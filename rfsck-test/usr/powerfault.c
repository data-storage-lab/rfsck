#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "powerfault.h"

const char *pfe_io_block_size_environ="PFE_IO_BLOCK_SIZE";
int pfe_io_block_size = 4096;



char* pfe_alloc_rand_mask(uint32_t length){
    char *buf = NULL;
    buf = (char *)calloc(length, 1);
    char *offset = buf;
    int rand_num = 0;
    int i = 0;
    for(i = 0; i < length/sizeof(int); ++i){
        rand_num = rand();	
        memcpy(offset, &rand_num, sizeof(int));
        offset += sizeof(int);
    }
    return buf; 
}

void pfe_free_rand_mask(char *buf){
    free(buf);
    return;
}

int pfe_addr_in_range(uint64_t offset){
    if(offset >= PFE_CORRUPT_LOWERBOUND && 
       offset <= PFE_CORRUPT_UPPERBOUND) {
        return 1;
    } else {
        return 0;
    }
}

uint64_t pfe_keep_in_range(uint64_t id, uint64_t lower, uint64_t upper){
    if(id < lower) 
        return lower;
    else if(id > upper)
        return upper;
    else
        return id;
}

int pfe_is_in_range(uint64_t id, uint64_t lower, uint64_t upper){
    if(id >= lower && id < upper) {
        return 1;
    } else {
        return 0;
    }
}



void pfe_print_scsi_cmd(struct scsi_cmd *cmd){
	printf("PFE:PFE: pfe_print_scsi_cmd(struct scsi_cmd *cmd)\n");
    //printf("PFE: sizeof(struct scsi_cmd) == %d\n", sizeof(struct scsi_cmd));
	//printf("PFE: *cmd == %p\n", cmd);
    //printf("PFE: cmd->c_target == %p (struct target *)\n", cmd->c_target);
    printf("PFE: cmd->c_target->name == %s \n", cmd->c_target->name);
    printf("PFE: cmd->c_target->tid == %d \n", cmd->c_target->tid);
    //printf("PFE: &(cmd->c_hlist) == %p (struct list_head)\n", &(cmd->c_hlist));
    //printf("PFE: &(cmd->qlist) == %p (struct list_head)\n", &(cmd->qlist));
    printf("PFE: cmd->dev_id == %"PRIu64" (uint64_t)\n", cmd->dev_id);//=1
    //printf("PFE: cmd->dev == %p (struct scsi_lu *)\n", cmd->dev);
    printf("PFE: cmd->state == %"PRIu64" (unsigned long)\n", cmd->state);
	printf("PFE: cmd->data_dir == %d (enum data_direction)\n", cmd->data_dir);
    //printf("PFE: cmd->in_sdb.resid == %d (int)\n", cmd->in_sdb.resid);
    printf("PFE: cmd->in_sdb.length == %"PRIu64" (uint32_t)\n", cmd->in_sdb.length);
    printf("PFE: cmd->in_sdb.buffer == %p (uint64_t)\n", cmd->in_sdb.buffer);
    printf("PFE: cmd->out_sdb.resid == %d (int)\n", cmd->out_sdb.resid);
    printf("PFE: cmd->out_sdb.length == %"PRIu64" (uint32_t)\n", cmd->out_sdb.length);
    printf("PFE: cmd->out_sdb.buffer == %p (uint64_t)\n", cmd->out_sdb.buffer);
	printf("PFE: cmd->cmd_itn_id == %"PRIu64" (uint64_t)\n", cmd->cmd_itn_id);
	printf("PFE: cmd->offset == %"PRIu64" (uint64_t)\n", cmd->offset);
	printf("PFE: cmd->tl == %u (uint32_t)\n", cmd->tl);
	//printf("PFE: cmd->scb == %p (uint8_t *)\n", cmd->scb);
    printf("PFE: cmd->scb[0] == %x\n", cmd->scb[0]);
    printf("PFE: cmd->scb_len == %d (int)\n", cmd->scb_len);
    //printf("PFE: &(cmd->lun[0]) == %p (uint8_t lun[8])\n", &(cmd->lun[0]));
    //printf("PFE: cmd->lun[0] == %x (uint8_t lun[8])\n", cmd->lun[0]);//=0
    //printf("PFE: cmd->lun[1] == %x (uint8_t lun[8])\n", cmd->lun[1]);//=1
    //printf("PFE: cmd->lun[2] == %x (uint8_t lun[8])\n", cmd->lun[2]);//=0
    //printf("PFE: cmd->attribut == %d (int)\n", cmd->attribute);//=32
	printf("PFE: cmd->tag == %"PRIu64" (uint64_t)\n", cmd->tag);
    printf("PFE: cmd->result == %d (int)\n", cmd->result);
	//printf("PFE: cmd->mreq == %p (struct mgmt_req *)\n", cmd->mreq);
	//printf("PFE: &(cmd->sense_buffer[0]) == %p (unsigned char)\n", &(cmd->sense_buffer[0]));
	//printf("PFE: cmd->sense_buffer[0] == %x (unsigned char)\n", cmd->sense_buffer[0]);
    //printf("PFE: cmd->sense_len == %d (int)\n", cmd->sense_len);//=0
    //printf("PFE: &(cmd->bs_list) == %p (struct list_head)\n", &(cmd->bs_list));
    //printf("PFE: cmd->it_nexus == %p (struct it_nexus *)\n", cmd->it_nexus);
    //printf("PFE: cmd->itn_lu_info == %p (struct it_nexus_lu_info *)\n", cmd->itn_lu_info);
    //
  fflush(stdout);

    
    return;
}

void pfe_print_scsi_cdb(uint8_t *scb){
    printf("PFE:PFE: pfe_print_scsi_cdb(uint8_t *scb)\n");
	switch (scb[0]) {
        case WRITE_10:
            printf("PFE: scb[0] == %x (Op Code)\n", scb[0]);
            uint8_t four_bytes[4];
            four_bytes[0] = scb[5];
            four_bytes[1] = scb[4];
            four_bytes[2] = scb[3];
            four_bytes[3] = scb[2];
            uint32_t *four_bytes_p = four_bytes;
            printf("PFE: scb[2-5] == %u (32-bit LBA, in bytes)\n", (*four_bytes_p)*512);
            uint8_t two_bytes[2];
            two_bytes[0] = scb[8];
            two_bytes[1] = scb[7];
            uint16_t *two_bytes_p = two_bytes;
            printf("PFE: scb[7-8] == %u (16-bit Transfer length, in bytes)\n", (*two_bytes_p)*512);
            break;
        default:
            printf("PFE: scb[0] == %x (Op Code)\n", scb[0]);
            printf("PFE: Not a WRITE_10 cmd!\n");
            break;
    }

    return;
}


void pfe_print_header(pfe_io_header_t *header){

    printf("PFE: IO Header\n");
    printf("PFE: header.id = %"PRIu64"\n", header->id);
    printf("PFE: header.ts = %"PRIu64"\n", header->ts);
    printf("PFE: header.offset = %"PRIu64"\n", header->offset);
    printf("PFE: header.length = %"PRIu64"\n", header->length);
    printf("PFE: header.datalog_offset = %"PRIu64"\n", header->datalog_offset);
    printf("PFE: header.cmd_type = %"PRIu64"\n", header->cmd_type);
    printf("PFE: header.data_dir = %"PRIu64"\n", header->data_dir);
    fflush(stdout);

    return;
}

int pfe_log_io_req(struct scsi_cmd *cmd, uint64_t offset,\
        uint64_t length, char *buf){

    printf("PFE:PFE: pfe_log_io_req(), pfe_io_id = %d\n", pfe_io_id);

    struct timeval t;
    gettimeofday(&t, 0); 
    uint64_t ts = t.tv_sec * 1000000ull + t.tv_usec;

    pthread_mutex_lock(&pfe_io_logs_mutex);

    pfe_io_header_t io_header;
    io_header.id = pfe_io_id;
    io_header.ts = ts;
    io_header.offset = offset;
    io_header.length = length;
    io_header.datalog_offset = pfe_io_datalog_offset;
    io_header.cmd_type = (uint64_t)cmd->scb[0];
    io_header.data_dir = (uint64_t)cmd->data_dir;
    io_header.tid = (uint64_t)cmd->c_target->tid;

    ++pfe_io_id;
    pfe_io_datalog_offset += length;
    pthread_mutex_unlock(&pfe_io_logs_mutex);

    int ret = 0;


    ret = pwrite(pfe_io_header_fd, &io_header, sizeof(pfe_io_header_t), sizeof(pfe_io_header_t)*io_header.id);
    if(ret < 0){
        printf("PFE: log io header failed! ret = %d \n", ret);
        return ret;
    }
    ret = pwrite(pfe_io_header_fd, &io_header.id, sizeof(uint64_t), 0);
    if(ret < 0){
        printf("PFE: update super_head failed! ret = %d \n", ret);
        return ret;
    }
    printf("PFE: logged IO# %"PRIu64" header to fd %d\n", io_header.id, pfe_io_header_fd);

    ret = pwrite(pfe_io_data_fd, buf, length, io_header.datalog_offset);
    if(ret < 0){
        printf("PFE: log io data failed! ret = %d \n", ret);
        return ret;
    }
    fsync(pfe_io_data_fd);
    printf("PFE: logged IO# %"PRIu64" data to fd %d\n", io_header.id, pfe_io_header_fd);

    return 0;

}

uint64_t pfe_get_io_cnt(int io_header_fd){

    pfe_io_header_t io_header;
    int ret;

    ret = pread(io_header_fd, &io_header, sizeof(pfe_io_header_t), 0);
    if(ret < 0){
        printf("PFE: ERROR in reading io_header log !!!\n");
        return -1; 
    }

    printf("PFE: total # of IO in log: %"PRIu64" \n", io_header.id);

    return io_header.id;
}

uint64_t pfe_split_io_log(int io_header_fd, int io_header_split_fd){

    uint64_t ret = 0;
    uint64_t tot_io_cnt = 0;
    uint64_t tot_splitted_io_cnt = 0;
    uint64_t i = 0;

    pfe_io_header_t io_header_orig;
    pfe_io_header_t io_header_split;

    tot_io_cnt =  pfe_get_io_cnt(io_header_fd);

    char * super_head = calloc(sizeof(pfe_io_header_t), 1);
    ret = pwrite(io_header_split_fd, super_head, sizeof(pfe_io_header_t), 0);
    if(ret < 0){
        printf("PFE: init sup_head failed! ret = %d \n", ret);
        return ret;
    }


    for(i = 1; i <= tot_io_cnt; ++i){

        uint64_t cur_offset = sizeof(pfe_io_header_t) * (i);
        ret = pread(io_header_fd, &io_header_orig, sizeof(pfe_io_header_t), cur_offset);
        if(ret < 0){
            printf("PFE: ERROR at pread #%"PRIu64" header from io_header log !!!\n", i);
            return -1; 
        }

        io_header_split.ts = io_header_orig.ts;
        io_header_split.cmd_type = io_header_orig.cmd_type;
        io_header_split.data_dir = io_header_orig.data_dir;
        io_header_split.tid = io_header_orig.tid;

        if(io_header_orig.length > pfe_io_block_size){

            uint64_t n_split = io_header_orig.length / pfe_io_block_size; 
            uint64_t n_split_remain = io_header_orig.length % pfe_io_block_size;

            int j;
            for(j = 0; j < n_split; ++j) {
                ++tot_splitted_io_cnt;
                io_header_split.id = tot_splitted_io_cnt;
                io_header_split.offset = io_header_orig.offset + pfe_io_block_size * j;
                io_header_split.length = pfe_io_block_size;
                io_header_split.datalog_offset = io_header_orig.datalog_offset + pfe_io_block_size * j;

                ret = pwrite(io_header_split_fd, &io_header_split, sizeof(pfe_io_header_t), sizeof(pfe_io_header_t)*io_header_split.id);
                if(ret < 0){
                    printf("PFE: log io header failed! ret = %d \n", ret);
                    return ret;
                }
            }
            if(n_split_remain != 0){
                ++tot_splitted_io_cnt;
                io_header_split.id = tot_splitted_io_cnt;
                io_header_split.offset = io_header_orig.offset + pfe_io_block_size * n_split;
                io_header_split.length = n_split_remain;
                io_header_split.datalog_offset = io_header_orig.datalog_offset + pfe_io_block_size * n_split;
                
                ret = pwrite(io_header_split_fd, &io_header_split, sizeof(pfe_io_header_t), sizeof(pfe_io_header_t)*io_header_split.id);
                if(ret < 0){
                    printf("PFE: log io header failed! ret = %d \n", ret);
                    return ret;
                }
            }
        
        }
        else{
            ++tot_splitted_io_cnt;
            io_header_split.id = tot_splitted_io_cnt;
            io_header_split.offset = io_header_orig.offset;
            io_header_split.length = io_header_orig.length;
            io_header_split.datalog_offset = io_header_orig.datalog_offset;
        
            ret = pwrite(io_header_split_fd, &io_header_split, sizeof(pfe_io_header_t), sizeof(pfe_io_header_t)*io_header_split.id);
            if(ret < 0){
                printf("PFE: log io header failed! ret = %d \n", ret);
                return ret;
            }
        }
    }

    ret = pwrite(io_header_split_fd, &tot_splitted_io_cnt, sizeof(uint64_t), 0);
    if(ret < 0){
        printf("PFE: update super_head failed! ret = %d \n", ret);
        return ret;
    }

    return ret;
}

uint64_t pfe_replay_simple(int io_header_fd, int io_data_fd, int disk_fd,\
        uint64_t first_id, uint64_t last_id){

    uint64_t ret = 0;
    uint64_t tot_io_cnt = 0;
    uint64_t replayed_cnt = 0;
    uint64_t i = 0;
    pfe_io_header_t io_header;

    tot_io_cnt = pfe_get_io_cnt(io_header_fd);

    for(i = first_id; i <= last_id; ++i){
        ++replayed_cnt;

        uint64_t cur_offset = sizeof(pfe_io_header_t) * (i);//skip the header
        ret = pread(io_header_fd, &io_header, sizeof(pfe_io_header_t), cur_offset);
        if(ret < 0){
            printf("PFE: ERROR at pread #%"PRIu64" header from io_header log !!!\n", i);
            return -1; 
        }
        
        char *data_buf = calloc(io_header.length, 1); 
        if(data_buf == NULL){
            printf("PFE: ERROR at calloc !!!\n");
            return -1;
        }
        ret = pread(io_data_fd, data_buf, io_header.length, io_header.datalog_offset);
        if(ret < 0){
            printf("PFE: ERROR at pread data #%"PRIu64", \
                    offset #%"PRIu64" at io_data log!!!\n", i, io_header.datalog_offset);
            return -1; 
        }

        ret = pwrite(disk_fd, data_buf, io_header.length, io_header.offset);
        if(ret < 0){
            printf("PFE: ERROR at replay data #%"PRIu64", \
                    offset #%"PRIu64" on disk file!!!\n", i, io_header.offset);
            return -1; 
        }
        free(data_buf);
    }

    printf("PFE: total replayed IO # = %"PRIu64"\n", replayed_cnt);

    return ret;
}


uint64_t pfe_do_normalwrite(int disk_fd, char *data_buf, uint64_t length, uint64_t offset){

    uint64_t ret = 0;
    ret = pwrite64(disk_fd, data_buf, length, offset);

    return ret;
}    

uint64_t pfe_replay_failure(int io_header_fd, int io_data_fd, int disk_fd, int fail_type, uint64_t start_id, uint64_t end_id, int err_blk_fd){

    uint64_t ret = 0;
    uint64_t tot_io_cnt = 0;
    uint64_t first_id = start_id; 
    uint64_t last_id = end_id;
    uint64_t i;
    pfe_io_header_t io_header;

    tot_io_cnt = pfe_get_io_cnt(io_header_fd);

    if(tot_io_cnt < end_id){
        last_id = tot_io_cnt;
    }

    if(first_id < 1){
        first_id = 1;
    }

    printf("PFE:PFE: REPLAY_w_FAILURE\n");
    printf("PFE: total # of IO recorded = %"PRIu64"\n", tot_io_cnt);
    printf("PFE: start replay from IO#= %"PRIu64"\n", start_id);
    printf("PFE: end replay at IO#= %"PRIu64"\n", last_id);
    printf("PFE: fail type = %d\n", fail_type);
  

    printf("PFE: do simple replay w/o failure.\n");
    pfe_replay_simple(io_header_fd, io_data_fd, disk_fd, first_id, last_id);

    return 0;
}


void pfe_build_errblks_cache(int err_blk_fd){

    uint64_t tot_blk_cnt = 0;

    int ret = pread(err_blk_fd, &tot_blk_cnt, sizeof(uint64_t), 0);
    if(ret != sizeof(uint64_t)){
        printf("PFE: ERROR in reading err_blk !!!\n");
    }
    printf("PFE: tot_blk_cnt = %"PRIu64"\n", tot_blk_cnt);

    uint64_t length = sizeof(uint64_t)*(tot_blk_cnt);
    pfe_errblks_tgtd.buf = calloc(length,1); 
    pfe_errblks_tgtd.length = length;
    pfe_errblks_tgtd.n_blks = tot_blk_cnt;


    ret = pread(err_blk_fd, pfe_errblks_tgtd.buf, length, sizeof(uint64_t));
    if(ret != length){
        printf("PFE: ERROR in reading err_blk !!!\n");
    }

}


void pfe_free_errblks_cache(){
    free(pfe_errblks_tgtd.buf);
}

//check if the req cover any err blk
int pfe_is_errblks(uint64_t offset, uint64_t length){

    uint64_t n_err_blks = pfe_errblks_tgtd.n_blks;
    uint64_t first_blk = offset/pfe_io_block_size;
    uint64_t after_last_blk = (offset+length)/pfe_io_block_size;
    uint64_t err_blk_num = 0;
    uint64_t buf_offset = 0;

    int i = 0;
    for(i = 0; i < n_err_blks; ++i){
        buf_offset = sizeof(uint64_t) * i;
        memcpy(&err_blk_num, pfe_errblks_tgtd.buf + buf_offset, sizeof(uint64_t));
        if(first_blk <= err_blk_num && err_blk_num < after_last_blk) {
            printf("PFE: read err_blk %"PRIu64": req offset %"PRIu64" \\
                    (blk %"PRIu64"), length %"PRIu64" (%"PRIu64" blks)\n",
                    err_blk_num, offset, first_blk, length, length/pfe_io_block_size);
            return 1;
        }
    }

    return 0;
}

int pfe_read(int fd, char * buf, uint64_t length, uint64_t offset,\
        struct scsi_cmd *cmd){
    int ret = 0;

    if(pfe_is_errblks(offset, length)){
       ret = -1; 
    }
    else{
       ret = pread64(fd, buf, length, offset);
    }

    return ret;
}


char * pfe_build_unser_pattern_cache(uint32_t * pattern_size){
	char * pattern_buf;
	char * pattern_file = getenv("UNSERIAL_PATTERN_FILE"); 
	printf(pattern_file);
	printf("\n");
	FILE * fp = fopen(pattern_file, "r");
	char line[3]; 
	uint32_t line_cnt = 0;
	uint32_t op_num = 0;

	if(fp != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			line_cnt ++;
		}
		fclose(fp);
		printf("PFE: ops in pattern = %u\n", line_cnt);
	}
	else{
		perror(pattern_file);	
		exit(EXIT_FAILURE);
	}

	*pattern_size = line_cnt;
	pattern_buf = calloc(line_cnt, 1);
	fp = fopen(pattern_file, "r");
	uint32_t i = 0;
	if(fp != NULL){
		while(fgets(line, sizeof(line), fp) != NULL){
			pattern_buf[i] = line[0];
			i++;
		}
		fclose(fp);
	}
	else{
		perror(pattern_file);	
		exit(EXIT_FAILURE);
	}
	
	return pattern_buf;
}

void pfe_free_unser_pattern_cache(char * pattern_buf){
	free(pattern_buf);
}
