#include "redo.h"


/*struct rfsck_txn {

  struct redo_block_tag txn_begin;
  
  struct redo_block_tag txn_end;

};*/

uint32_t hash(char *str)
    {
        uint32_t hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

int write_info(int fd, uint64_t offset, uint32_t size, const void *buf, int count_offset) {

    //printf("Writing buffer of size %" PRIu32 " to offset %" PRIu64 " \n\n", size, offset);
    ssize_t retval =  pwrite(fd, buf, (size_t) size, (off_t)offset);
    if(retval < 0) {
        printf("Unable to write record of size %" PRIu32 " to offset %" PRIu64 " \n\n", size, offset);
        return 1;
    } else if(retval != size) {
        printf("Unable to write record of size %" PRIu32 " to offset %" PRIu64 " \n\n", size, offset);
        return 1;

    }

    if(count_offset)
        redo_data->log_offset += size;

    return 0;
}

int rfsck_txn_begin() {

    int retval;
    redo_data->keyb->tags[redo_data->keys_in_block].offset  = 0;
    redo_data->keyb->tags[redo_data->keys_in_block].size    = 0;
    redo_data->keyb->tags[redo_data->keys_in_block].blk_crc = redo_data->txn_id;


    uint32_t tag_crc = crc32c_le(~0, (unsigned char *) &redo_data->keyb->tags[redo_data->keys_in_block], sizeof(struct redo_block_tag));

    redo_data->txn_csum = TXN_CHKSM_CNST ^ tag_crc;

    //printf("TXN_BEGIN: %ld - %ld - %ld - %ld\n", redo_data->num_keys, redo_data->txn_id, redo_data->keys_in_block, redo_data->txn_csum);    
    //retval = write_info(redo_data->redo_fd, redo_data->log_offset, size, buf, 1);

    if(retval)
        return retval;

    redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
    redo_data->keyb->reserved = 0;
    redo_data->keyb->crc   = 0;
    redo_data->keyb->crc   = crc32c_le(~0, (unsigned char *)redo_data->keyb, REDO_LOG_BLOCK_SIZE);

    redo_data->keys_in_block++;

    retval = write_info(redo_data->redo_fd, redo_data->redo_block_offset,
                                            REDO_LOG_BLOCK_SIZE, redo_data->keyb, 0);

    if(retval)
        return retval;

    if(redo_data->keys_in_block ==  KEYS_PER_BLOCK(redo_data)) {
        redo_data->keyb = calloc(1, REDO_LOG_BLOCK_SIZE);
        redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
        redo_data->keyb->crc   = 0;

        redo_data->keys_in_block = 0;
        redo_data->num_keys++;
        redo_data->redo_block_offset = redo_data->log_offset;
        redo_data->log_offset += REDO_LOG_BLOCK_SIZE;
    }

    return 0;
}

int rfsck_txn_end() {

    int retval;
    redo_data->keyb->tags[redo_data->keys_in_block].offset  = 0;  //TODO store txn checksum
    redo_data->keyb->tags[redo_data->keys_in_block].size    = 0;
    redo_data->keyb->tags[redo_data->keys_in_block].blk_crc = redo_data->txn_id;


    uint32_t tag_crc = crc32c_le(~0, (unsigned char *) &redo_data->keyb->tags[redo_data->keys_in_block], sizeof(struct redo_block_tag));

    redo_data->txn_csum = redo_data->txn_csum ^ tag_crc;

    redo_data->keyb->tags[redo_data->keys_in_block].offset = redo_data->txn_csum;
 
    //retval = write_info(redo_data->redo_fd, redo_data->log_offset, size, buf, 1);

    //printf("TXN_END: %ld - %ld - %ld - %ld\n", redo_data->num_keys, redo_data->txn_id, redo_data->keys_in_block, redo_data->txn_csum);

    
    redo_data->keys_in_block++;
    redo_data->txn_id++;
    //if(retval)
    //    return retval;

    redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
    redo_data->keyb->reserved = 0;
    redo_data->keyb->crc   = 0;
    redo_data->keyb->crc   = crc32c_le(~0, (unsigned char *)redo_data->keyb, REDO_LOG_BLOCK_SIZE);

    retval = write_info(redo_data->redo_fd, redo_data->redo_block_offset,
                                            REDO_LOG_BLOCK_SIZE, redo_data->keyb, 0);

    if(retval)
        return retval;

    if(redo_data->keys_in_block ==  KEYS_PER_BLOCK(redo_data)) {
        redo_data->keyb = calloc(1, REDO_LOG_BLOCK_SIZE);
        redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
        redo_data->keyb->crc   = 0;

        redo_data->keys_in_block = 0;
        redo_data->num_keys++;
        redo_data->redo_block_offset = redo_data->log_offset;
        redo_data->log_offset += REDO_LOG_BLOCK_SIZE;
    }


    redo_data->txn_csum = 0;

    rfsck_flush();

    return 0;

}

int redo_setup(int dev_fd, int redo_fd) {
    int retval = 0;

    if(!redo_data) {
        redo_data = malloc(sizeof(struct redo_private_data));
        if(!redo_data)
             return 1;
        redo_data->tdb_written = 0;
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
  
    uint32_t hdr_crc = crc32c_le(~0, (unsigned char *)&redo_data->hdr, 
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
    
    //memset(&redo_data->keyb, 0, REDO_LOG_BLOCK_SIZE);
    redo_data->keyb = calloc(1, REDO_LOG_BLOCK_SIZE);
    redo_data->log_offset += sizeof(redo_data->hdr); 

    
    
    //TODO set superblock (determine the offset and size of superblock for various file systems)
    
    redo_data->hdr.key_offset = redo_data->log_offset;
    redo_data->redo_block_offset = redo_data->log_offset;
    redo_data->keys_in_block = 0;
    redo_data->num_keys = 0;

    redo_data->log_offset += REDO_LOG_BLOCK_SIZE;   

    redo_data->txn_id = 1;
 
    return 0;
}

int rfsck_open(char *redo, int dev_fd, int flags) {


    int retval = 1;
    if(!redo) {
         printf("REDO: Redo file name empty");
         return 1;
    }

    if(dev_fd < 1) {
         printf("REDO: FD of dev file empty");
         return 1;
    }

    int open_flags = 0;
    int redo_fd = 0;

    //if(flags & O_EXCL)
    //     open_flags |= O_EXCL;

    //if(flags & O_RDWR)
      //   open_flags |= O_RDWR;
    //else
    //     open_flags |= O_RDONLY;

    //if(flags & O_DIRECT)
    //     open_flag |= O_DIRECT;

    /*if(flags & O_SYNC)
         open_flags |= O_SYNC;*/

    //open_flags |= O_CREAT;

    redo_fd = open(redo, O_RDWR | O_CREAT, 0666);

    if(redo_fd == -1) {
        printf("REDO: Unable to open redo file: %s\n", redo);
        return 1;
    }

    redo_fd = open(redo, O_RDWR);
    if(redo_fd == -1) {
        printf("REDO: Unable to open redo file: %s\n", redo);
        return 1;
    }

    redo_setup(dev_fd, redo_fd); 
    rfsck_replay(1);

    retval =  write_info(redo_data->redo_fd, 0, sizeof(redo_data->hdr), &redo_data->hdr, 0);
    if(retval) {
        printf("Unable to write Redo Header Information");
        return retval;
    }

    return retval;
}

int rfsck_write(uint64_t offset, uint32_t size, void* buf) {

    int retval = 0;
    redo_data->keyb->tags[redo_data->keys_in_block].offset = offset;
    redo_data->keyb->tags[redo_data->keys_in_block].size   = size;
    redo_data->keyb->tags[redo_data->keys_in_block].blk_crc = crc32c_le(~0, buf, size);
    //printf("Redo tag[%ld-%ld]: doffset = %ld, offset = %ld, size = %ld\n",redo_data->num_keys, redo_data->keys_in_block, redo_data->log_offset, offset, size);

    uint32_t tag_crc = crc32c_le(~0, (unsigned char *) &redo_data->keyb->tags[redo_data->keys_in_block], sizeof(struct redo_block_tag));
    redo_data->txn_csum = redo_data->txn_csum ^ tag_crc;

    //printf("Redo tag[%ld - %ld]: checksum = %ld\n", redo_data->num_keys, redo_data->keys_in_block, redo_data->txn_csum);

    retval = write_info(redo_data->redo_fd, redo_data->log_offset, size, buf, 1);

    if(retval)
        return retval;


    redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
    redo_data->keyb->reserved = 0;
    redo_data->keyb->crc   = 0;
    redo_data->keyb->crc   = crc32c_le(~0, (unsigned char *)redo_data->keyb, REDO_LOG_BLOCK_SIZE);

    retval = write_info(redo_data->redo_fd, redo_data->redo_block_offset, 
                                            REDO_LOG_BLOCK_SIZE, redo_data->keyb, 0);

    if(retval)
        return retval;
    
    redo_data->keys_in_block++;

    if(redo_data->keys_in_block ==  KEYS_PER_BLOCK(redo_data)) {
        //printf("Redo Block-%ld offset: %ld\n", redo_data->num_keys, redo_data->redo_block_offset);
        redo_data->keyb = calloc(1, REDO_LOG_BLOCK_SIZE);
        redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
        redo_data->keyb->crc   = 0;
        redo_data->keys_in_block = 0;
        redo_data->num_keys++;
        redo_data->redo_block_offset = redo_data->log_offset;
        redo_data->log_offset += REDO_LOG_BLOCK_SIZE;
    }


    return retval;
}

int records_written() {


    if(!redo_data)
        return 1;

    if(redo_data->keys_in_block > 0)
        return 0;
    else if(redo_data->keys_in_block == 0 && redo_data->num_keys > 0)
        return 0;
    else
        return 1;

}

int rfsck_replay(int flush) {
    
    int retval = 0;

    if(!redo_data) {

        //redo_data = malloc(sizeof(struct redo_private_data));
        //if(!redo_data)
             return 1;

        
    }
    //TODO add logic to open redo log for replay

    /*struct stat file_stat;
 
    retval = fstat(redo_data->redo_fd, &file_stat);

    if(retval)
       return retval;

    if(file_stat.st_size == 0)
        return 0;
    */
    struct redo_header *hdr;
    struct redo_block  *keyb;
    struct redo_block_tag *blk_tag;
    int verify_checksum = 0;

    uint64_t log_offset = 0, replay_log_offset = 0;
    uint32_t hdr_crc, block_crc, data_crc;
    //uint64_t redo_block_offset;

    redo_data->redo_block_size = REDO_LOG_BLOCK_SIZE;

    hdr  = malloc(sizeof(struct redo_header));
    
    retval = pread64(redo_data->redo_fd, hdr, sizeof(struct redo_header), 0);

    if(retval < 0) {
        printf("Unable to read header\n\n");
        return retval;
    }

    log_offset += sizeof(struct redo_header);
    replay_log_offset = log_offset;
    //if(memcmp(hdr->magic, REDO_HEADER_MAGIC_NUMBER, sizeof(REDO_HEADER_MAGIC_NUMBER))) {
    //printf("X-%s-X\n", hdr->magic);
    /*if(strcmp(hdr->magic, REDO_HEADER_MAGIC_NUMBER)) {
        printf("Header magic number mismatch\n\n");
        return 1;
    } */

    //TODO verify Header check sum
    hdr_crc = hdr->header_crc;
    hdr->header_crc = 0;

    hdr->header_crc = crc32c_le(~0, (unsigned char *)hdr, sizeof(struct redo_header));

    if(hdr_crc != hdr->header_crc) {
        printf("REDO: Redo Header checksum mismatch\n\n");
        if(hdr)
            free(hdr);

        return 1;
    }

    /*if(hdr->state != E2REDO_STATE_FINISHED) {
        printf("Redo log is incomplete\n\n");
        if(hdr)
            free(hdr);

        return 1;
    }*/

    //TODO verify file-system information

    keyb = malloc(REDO_LOG_BLOCK_SIZE);

    int count = 0, keyb_count, keys_per_block;

    keys_per_block = KEYS_PER_BLOCK(redo_data);
 
    char *buf = 0;
    uint32_t txn_id = 0;
    uint32_t txn_csum, txn_end_csum, temp_csum;
    struct replay_block *replay_blocks;
    uint64_t *keys_offset;
    int is_replayed = 0;

    keys_offset = calloc(hdr->num_keys + 1, sizeof(uint64_t));
    memset(keys_offset, 0, (hdr->num_keys + 1) * sizeof(uint64_t));

    replay_blocks = calloc(hdr->num_keys, REDO_LOG_BLOCK_SIZE);
    memset(replay_blocks, 0, hdr->num_keys * REDO_LOG_BLOCK_SIZE);
    //printf("Size of replay_blocks: %ld\n", hdr->num_keys * REDO_LOG_BLOCK_SIZE);
//rerun:
    keyb_count = 0;
    log_offset = hdr->key_offset;
    redo_data->txn_id = 0;
    redo_data->txn_csum = 0;
    redo_data->txn_begin_blk = 0;
    redo_data->txn_begin_idx = 0;
    replay_log_offset += REDO_LOG_BLOCK_SIZE;
    while(keyb_count <= hdr->num_keys) {
        //printf("log offset: %ld\n", log_offset);
        retval = pread64(redo_data->redo_fd, keyb, REDO_LOG_BLOCK_SIZE, log_offset);
        if(retval < 0) {
            printf("Unable to read key block\n");
            goto free_end;
        }

        keys_offset[keyb_count] = log_offset;
        printf("Key Offsets: %ld - %ld\n", keyb_count, log_offset);
        //printf("keyb val: magic = %ld, crc = %ld, size1 = %ld\n",keyb->magic, keyb->crc, keyb->tags[0].size);
        //memcpy(&redo_data->blocks[keyb_count], keyb, REDO_LOG_BLOCK_SIZE);
        //memcpy(&replay_blocks[keyb_count], keyb, REDO_LOG_BLOCK_SIZE);
        replay_blocks[keyb_count].magic = keyb->magic;
        replay_blocks[keyb_count].crc   = keyb->crc;
        int num = 0;
        for(num = 0; num < keys_per_block; num++) {
                replay_blocks[keyb_count].tags[num].size    = keyb->tags[num].size;
                replay_blocks[keyb_count].tags[num].offset  = keyb->tags[num].offset;
                replay_blocks[keyb_count].tags[num].blk_crc = keyb->tags[num].blk_crc;
        }
        //printf("redo_data[%ld] val: magic = %ld, crc = %ld, size1 = %ld\n", keyb_count,replay_blocks[keyb_count].magic, replay_blocks[keyb_count].crc, replay_blocks[keyb_count].tags[0].size);
        /*for(num = 0; num <= keyb_count; num++) { 
            printf("replay_data[%ld] val: magic = %ld, crc = %ld, size1 = %ld\n", num,replay_blocks[num].magic, replay_blocks[num].crc, replay_blocks[num].tags[0].size);
        }*/
        //memcpy(redo_data->blocks[keyb_count], keyb, REDO_LOG_BLOCK_SIZE);
        //redo_data->blocks[keyb_count] = keyb;
        log_offset += REDO_LOG_BLOCK_SIZE;


        //verify the following parameters of each transaction
        //    - checksum in txn_end index
        //    - txn replayed or not
        count = 0;
        for(blk_tag = keyb->tags; 
                   blk_tag != NULL && count < keys_per_block;
                          blk_tag++, count++) {
            log_offset += blk_tag->size;
            if(blk_tag->size == 0 && blk_tag->blk_crc == 0 && blk_tag->offset == 0)
                continue;

            if(blk_tag->size == 0 && blk_tag->blk_crc > 0) {
                if(redo_data->txn_id == 0) {
                    // this is txn_begin index record
                    redo_data->txn_id  = blk_tag->blk_crc;
                    if(blk_tag->offset == TXN_REPLAYED_CNST) {
                        is_replayed = 1;
                        printf("Transaction %ld already replayed, skipping this\n", blk_tag->blk_crc);
                        continue;
                    } else {
                        is_replayed = 0;
                    }
                    redo_data->txn_begin_blk = keyb_count;
                    redo_data->txn_begin_idx = count;

                    temp_csum= crc32c_le(~0, (unsigned char *) blk_tag, sizeof(struct redo_block_tag));
                    redo_data->txn_csum = TXN_CHKSM_CNST ^ temp_csum;

                    printf("Replay:: TXN_BEGIN: %ld - %ld - %ld - %ld\n", keyb_count,
                                         count, redo_data->txn_id, redo_data->txn_csum);
                } else {
                    // this is txn_end index record
                    if(is_replayed) {
                        redo_data->txn_id  = 0;
                        continue;
                    }
                    txn_end_csum = blk_tag->offset;
                    blk_tag->offset = 0;
                    temp_csum = crc32c_le(~0, (unsigned char *) blk_tag, 
                                                       sizeof(struct redo_block_tag));

                    redo_data->txn_csum = redo_data->txn_csum ^ temp_csum;
                    printf("Replay:: TXN_END: %ld - %ld - %ld - %ld\n", keyb_count,
                                         count, redo_data->txn_id, redo_data->txn_csum); 
                    if(txn_end_csum != redo_data->txn_csum) {
                        printf("Checksum mismatch for Transaction (tid=%ld)\n", redo_data->txn_id);
                    }

                    // Replay txn records
                    int i = 0, j = 0, txn_replayed = 0;
                    for(i = redo_data->txn_begin_blk; i <= keyb_count && txn_replayed == 0; i++) {

                        if(i == redo_data->txn_begin_blk)
                            j = redo_data->txn_begin_idx + 1;
                        else
                            j = 0;

                        while(j < keys_per_block) {
                            if(i == keyb_count && j == count) {
                                txn_replayed = 1;
                                break;
                            }

                            // Replay redo data blocks

                            buf = malloc(replay_blocks[i].tags[j].size);

                            retval = pread64(redo_data->redo_fd, buf, 
                                              replay_blocks[i].tags[j].size,
                                              replay_log_offset);
                            if(retval < 0) {
                                printf("Unable to read data block\n");
                                if(buf)
                                    free(buf);

                                goto free_end;
                            }
                            //printf("Replay tag[%ld-%ld]:doffset = %ld, offset = %ld, size = %ld\n", i, j, replay_log_offset, replay_blocks[i].tags[j].offset, replay_blocks[i].tags[j].size);
                            retval = write_info(redo_data->dev_fd, 
                                            replay_blocks[i].tags[j].offset, 
                                            replay_blocks[i].tags[j].size, buf, 0); 
                            if(retval) {
                                if(buf)
                                    free(buf);

                                goto free_end;
                            }
                            replay_log_offset += replay_blocks[i].tags[j].size;
                            j++;
                            buf = 0;
                        }

                        if(j == keys_per_block)
                            replay_log_offset += REDO_LOG_BLOCK_SIZE;
                    }
                     
                    // Mark txn as replayed
                    replay_blocks[redo_data->txn_begin_blk].tags[redo_data->txn_begin_idx].offset = TXN_REPLAYED_CNST;

                    retval = write_info(redo_data->redo_fd, 
                                            keys_offset[redo_data->txn_begin_blk], 
                                            REDO_LOG_BLOCK_SIZE, 
                                            (void *) (replay_blocks + redo_data->txn_begin_blk), 0);
                     
                    // After replay reset txn_id, txn_csum, txn_begin_blk, txn_begin_idx
                    redo_data->txn_id  = 0;
                    redo_data->txn_csum = 0;
                    redo_data->txn_begin_blk = 0;
                    redo_data->txn_begin_idx = 0;
                }

            } else {
                // Calculate checksum of regular index blocks

                if(is_replayed)
                    continue;
                temp_csum = crc32c_le(~0, (unsigned char *) blk_tag, 
                                                 sizeof(struct redo_block_tag)); 
                redo_data->txn_csum = redo_data->txn_csum ^ temp_csum;
                //printf("Replay:: Redo tag[%ld - %ld]: csum = %ld\n", keyb_count, count, redo_data->txn_csum);
            }
        }
    keyb_count++;    
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

int redo_mark_done(int mark_done) {
    int retval = 0;

    if(!redo_data)
        return retval;

    redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
    redo_data->keyb->crc   = 0;
    redo_data->keyb->crc   = crc32c_le(~0, (unsigned char *)redo_data->keyb, 
                                                                  REDO_LOG_BLOCK_SIZE);

    retval = write_info(redo_data->redo_fd, redo_data->redo_block_offset,
                                            REDO_LOG_BLOCK_SIZE, redo_data->keyb, 0); 

    if(retval)
        return retval;

    retval = rfsck_flush();

    if(retval)
        return retval;

    redo_data->hdr.num_keys   = redo_data->num_keys;
    if(mark_done)
        redo_data->hdr.state  = 1;
    else
        redo_data->hdr.state  = 0;

    redo_data->hdr.header_crc = 0;
    uint32_t hdr_crc = crc32c_le(~0, (unsigned char *)&redo_data->hdr,
                                   sizeof(redo_data->hdr));

    redo_data->hdr.header_crc = hdr_crc;

    retval = write_info(redo_data->redo_fd, 0, sizeof(redo_data->hdr), &redo_data->hdr, 0);

    if(retval)
        return retval;

    retval = rfsck_flush();

    if(retval)
        return retval;

    return retval;
}

int rfsck_close() {

  //TODO add function call to redo_flush 
   /* int retval;

    retval = redo_mark_done();
    if(retval)
        return retval;

    retval = redo_replay(1);
    */

    if(redo_data) {
        int cl = close(redo_data->redo_fd);
        if(cl < 0) {
            return cl;
        }

        //free(redo_data);
    }
    return 0;

}


int rfsck_flush() {

    int retval = 0;

    if(redo_data) {

        redo_data->keyb->magic = hash(REDO_BLOCK_MAGIC_NUMBER);
        redo_data->keyb->crc   = 0;
        redo_data->keyb->crc   = crc32c_le(~0, (unsigned char *)redo_data->keyb,
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
