#include "redo.h"


uint32_t hash(unsigned char *str)
    {
        uint32_t hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

int write_info(int fd, uint64_t offset, uint32_t size, void *buf, int count_offset) {

    int retval =  pwrite64(fd, buf, size, offset);
    if(retval < 0) {
        printf("Unable to write record of size %llu to offset %llu", size, offset);
        return 1;
    }

    if(count_offset)
        redo_data->log_offset += size;

    return 0;
}

int redo_setup(int dev_fd, int redo_fd) {
    int retval = 0;

    if(!redo_data) {
        redo_data = malloc(sizeof(struct redo_private_data));
        if(!redo_data)
             return 1;
    }

    if(redo_data->tdb_written)
        return retval;

    redo_data->tdb_written = 1;


    redo_data->redo_fd     = redo_fd;
    redo_data->dev_fd      = dev_fd;
    redo_data->log_offset  = 0;

    redo_data->redo_block_size = REDO_LOG_BLOCK_SIZE;

    

    /* Write the redo header to the disk */
    memcpy(redo_data->hdr.magic, REDO_HEADER_MAGIC_NUMBER, sizeof(redo_data->hdr.magic));
    redo_data->hdr.num_keys = 0;
    redo_data->hdr.state = 0; // Initially set to 0
    redo_data->hdr.super_offset = 0;
    redo_data->hdr.key_offset = sizeof(struct redo_header);
    redo_data->hdr.sb_crc     = 0;

    redo_data->hdr.header_crc = 0;
  
    uint32_t hdr_crc = ext2fs_crc32c_le(~0, (unsigned char *)&redo_data->hdr, 
                                                           sizeof(redo_data->hdr));

    redo_data->hdr.header_crc = hdr_crc;

/*    retval = write_info(data->redo_fd, data->log_offset, sizeof(data->hdr), &data->hdr, 1);
   
    if(retval)
        return retval;

    retval =  pwrite64(data->redo_fd, &data->hdr, sizeof(data->hdr), data->log_offset);
    if(retval) {
        printf("Unable to write Redo Header Information");
        return retval;
    } */
    redo_data->log_offset += sizeof(redo_data->hdr); 

    memset(redo_data->keyb, 0, REDO_LOG_BLOCK_SIZE);
    
    //TODO set superblock (determine the offset and size of superblock for various file systems)
    
    redo_data->hdr.key_offset = redo_data->log_offset;
    redo_data->redo_block_offset = redo_data->log_offset;
    
    return 0;
}

int redo_open(char *redo, int dev_fd, int flags) {


    int retval = 0;
    if(redo) {
         printf("REDO: Redo file name empty");
         return 1;
    }

    if(dev_fd < 1) {
         printf("REDO: FD of dev file empty");
         return 1;
    }

    int open_flags = 0;
    int redo_fd = 0;

    if(flags & O_EXCL)
         open_flags |= O_EXCL;

    if(flags & O_RDWR)
         open_flags |= O_RDWR;
    else
         open_flags |= O_RDONLY;

    //if(flags & O_DIRECT)
    //     open_flag |= O_DIRECT;

    if(flags & O_SYNC)
         open_flags |= O_SYNC;

    open_flags |= O_CREAT;

    redo_fd = open(redo, open_flags);

    if(redo_fd == -1) {
        printf("REDO: Unable to open redo file: %s", redo);
        return 1;
    }

    redo_setup(dev_fd, redo_fd); 
    redo_replay(1);

    retval =  write_info(redo_data->redo_fd, redo_data->log_offset, sizeof(redo_data->hdr), &redo_data->hdr, 1);
    if(retval) {
        printf("Unable to write Redo Header Information");
        return retval;
    }

    return retval;
}

int redo_close() {

  //TODO add function call to redo_flush 


    int cl = close(redo_data->redo_fd);
    if(cl < 0) {
        return cl;
    }


    free(redo_data);

    return 0;

}

int redo_write(uint64_t offset, uint32_t size, void* buf) {

    int retval = 0;
    struct redo_block_tag *tag;

    tag = redo_data->keyb->tags + redo_data->keys_in_block;

    tag->offset = offset;
    tag->size   = size;

    tag->blk_crc = ext2fs_crc32c_le(~0, buf, size);
    redo_data->keys_in_block++;


    retval = write_info(redo_data->redo_fd, redo_data->log_offset, size, buf, 1);

    if(retval)
        return retval;

    /*retval = pwrite64(data->redo_fd, buf, tag->size, tag->offset);
    
    if(retval) {
        printf("Unable to write record of size %llu to offset %llu", tag->size, tag->offset);
        return retval;
    }
    data->log_offset += sizeof(data->hdr);    */

    redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
    redo_data->keyb->crc   = 0;
    redo_data->keyb->crc   = ext2fs_crc32c_le(~0, (unsigned char *)redo_data->keyb, REDO_LOG_BLOCK_SIZE);

    retval = write_info(redo_data->redo_fd, redo_data->redo_block_offset, 
                                            REDO_LOG_BLOCK_SIZE, redo_data->keyb, 0);

    if(retval)
        return retval;

    if(redo_data->keys_in_block == KEYS_PER_BLOCK(redo_data)) {
        memset(redo_data->keyb, 0, REDO_LOG_BLOCK_SIZE);
        redo_data->keys_in_block = 0;
        redo_data->num_keys++;
        redo_data->log_offset += REDO_LOG_BLOCK_SIZE;
    }


    return retval;
}

int redo_replay(int flush) {
    
    int retval = 0;

    if(!redo_data) {

        //redo_data = malloc(sizeof(struct redo_private_data));
        //if(!redo_data)
             return 1;

        
    }
    //TODO add logic to open redo log for replay

    struct stat file_stat;
 
    retval = fstat(redo_data->redo_fd, &file_stat);

    if(retval)
       return retval;

    if(file_stat.st_size == 0)
        return 0;

    struct redo_header *hdr;
    struct redo_block  *keyb;
    struct redo_block_tag *blk_tag;
    int verify_checksum = 1;

    uint64_t log_offset = 0;
    uint64_t redo_block_offset;

    hdr  = malloc(sizeof(struct redo_header));
    
    retval = pread64(redo_data->redo_fd, hdr, sizeof(struct redo_header), 0);

    if(retval < 0) {
        printf("Unable to read header");
        return retval;
    }

    log_offset += sizeof(struct redo_header);

    if(memcmp(hdr->magic, REDO_HEADER_MAGIC_NUMBER, sizeof(REDO_HEADER_MAGIC_NUMBER))) {
        printf("Header magic number mismatch");
        return 1;
    } 

    //TODO verify Header check sum

    if(hdr->state != E2REDO_STATE_FINISHED) {
        printf("Redo log is incomplete\n\n");
        goto free_end;
    }

    //TODO verify file-system information

    keyb = malloc(sizeof(struct redo_block));

    int count, keyb_count = 0;
 
    char *buf;

rerun:

    log_offset = hdr->key_offset;
    while(keyb_count <= hdr->num_keys) {
 
        retval = pread64(redo_data->redo_fd, keyb, REDO_LOG_BLOCK_SIZE, log_offset);
        if(retval < 0) {
            printf("Unable to read key block\n");
            goto free_end;
            //return retval;
        }

        log_offset += REDO_LOG_BLOCK_SIZE;

        if(verify_checksum) {
            if(hash(REDO_BLOCK_MAGIC_NUMBER) != keyb->magic) {
                printf("Redo block mismatch\n\n");
                goto free_end;
            }
            //TODO verify checksum of redo block
        }

        count = 0;
        for(blk_tag = keyb->tags; 
                   blk_tag != NULL && blk_tag->offset > 0 && count <= KEYS_PER_BLOCK(redo_data);
                          blk_tag++, count++) {
            buf = malloc(blk_tag->size);
            retval = pread64(redo_data->redo_fd, buf, blk_tag->size, log_offset);

            if(retval < 0) {
                printf("Unable to read data block\n");
                free(buf);
                goto free_end;
            }
            
            if(verify_checksum) {
              //TODO verify checksum of data block
            } else {
                retval = write_info(redo_data->dev_fd, blk_tag->offset, blk_tag->size, buf, 0); 
                if(retval) {
                    free(buf);
                    goto free_end;
                }
            }

            free(buf);

        }
        
    }

    if(verify_checksum) {
        verify_checksum = 0;
        goto rerun;
    }

    if(flush)
        retval = fsync(redo_data->dev_fd);

free_end:
    if(hdr)
        free(hdr);
    if(keyb)
        free(keyb);

    return retval;
}

int redo_mark_done() {
    int retval = 0;

    if(!redo_data)
        return retval;

    redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
    redo_data->keyb->crc   = 0;
    redo_data->keyb->crc   = ext2fs_crc32c_le(~0, (unsigned char *)redo_data->keyb, 
                                                                  REDO_LOG_BLOCK_SIZE);

    retval = write_info(redo_data->redo_fd, redo_data->redo_block_offset,
                                            REDO_LOG_BLOCK_SIZE, redo_data->keyb, 0); 

    if(retval)
        return retval;

    retval = redo_flush();

    if(retval)
        return retval;

    redo_data->hdr.num_keys   = redo_data->num_keys;
    redo_data->hdr.state      = 1;

    redo_data->hdr.header_crc = 0;
    uint32_t hdr_crc = ext2fs_crc32c_le(~0, (unsigned char *)&redo_data->hdr,
                                   sizeof(redo_data->hdr));

    redo_data->hdr.header_crc = hdr_crc;

    retval = write_info(redo_data->redo_fd, 0, sizeof(redo_data->hdr), &redo_data->hdr, 0);

    if(retval)
        return retval;

    retval = redo_flush();

    if(retval)
        return retval;

    return retval;
}

int redo_flush() {

    int retval = 0;

    if(redo_data) {

        redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
        redo_data->keyb->crc   = 0;
        redo_data->keyb->crc   = ext2fs_crc32c_le(~0, (unsigned char *)redo_data->keyb,
                                                                  REDO_LOG_BLOCK_SIZE);

        retval = write_info(redo_data->redo_fd, redo_data->redo_block_offset,
                                            REDO_LOG_BLOCK_SIZE, redo_data->keyb, 0);

        if(retval)
            return retval;

        retval = fsync(redo_data->redo_fd);
        return retval;

    }
    return 1;
       

}
