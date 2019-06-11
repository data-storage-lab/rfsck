/* mai: power fault emulator project*/
#ifndef __POWERFAULT_H
#define __POWERFAULT_H

#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/time.h>
#include <stdbool.h>


#include "list.h"
#include "util.h"
#include "tgtd.h"
#include "scsi.h"
#include "spc.h"
#include "bs_thread.h"
#include "target.h"


#define ENABLE_RECORD 1

//add more of failure scenarios
#define PFE_NORMAL 0

#define PFE_RET_ERRNO5 7
#define PFE_RET_HANG 8
#define PFE_CORRUPT_LOWERBOUND 1000 
#define PFE_CORRUPT_UPPERBOUND (4096*3-1) 

#define PFE_SHORN_NEW_DATA_SIZE (512*7) 

#define PFE_FIRST_CORRUPT_BEFORE_CUT 0 
#define PFE_CORRUPT_RANGE 1 
#define PFE_FIRST_FLY_BEFORE_CUT  10  
#define PFE_FLY_OFFSET (4096*2)  
#define PFE_FIRST_UNSERIAL_BEFORE_CUT 9 
#define PFE_UNSERIAL_RANGE 8 
#define PFE_FIRST_ERR_BEFORE_CUT 10 
#define PFE_ERR_RANGE 3 

#define PFE_BLOCK_SIZE 512 

extern const char *pfe_io_block_size_environ;
extern int pfe_io_block_size;

inline static void config_pfe_io_block_size() {
    char *tmp = NULL;
    tmp = getenv(pfe_io_block_size_environ);
    if (tmp == NULL) {
        fprintf(stderr, "config_pfe_io_block_size:%s doesn't exist,"
                "use default value %d.\n",
                pfe_io_block_size_environ, pfe_io_block_size);
    } else {
        fprintf(stderr, "config_pfe_io_block_size:%s exist,"
                "use its value %s.\n",
                pfe_io_block_size_environ, tmp);
       pfe_io_block_size = atoi(tmp);
    }   
}


//metadata for each recorded io
typedef struct pfe_io_header {
    uint64_t id; //IO#
    uint64_t ts; //timestamp
    uint64_t offset;
    uint64_t length;
    uint64_t datalog_offset;
    uint64_t cmd_type;
    uint64_t data_dir;
    //uint64_t marker; 
    uint64_t tid; //cmd->c_target->tid
} pfe_io_header_t;


typedef struct pfe_errblks_cache {
    char * buf;
    uint64_t length; //size in bytes
    uint64_t n_blks; // # of 4KB blks
} pfe_errblks_cache_t;


extern int pfe_io_header_fd;
extern int pfe_io_data_fd;
extern int pfe_err_blk_fd;
extern uint64_t pfe_io_id;
extern uint64_t pfe_io_datalog_offset;
extern pthread_mutex_t pfe_io_logs_mutex;
extern int pfe_fail_type_tgtd;
extern pfe_errblks_cache_t pfe_errblks_tgtd;
extern int pfe_enable_record;


char* pfe_alloc_rand_mask(uint32_t length);
void pfe_free_rand_mask(char *buf);

int pfe_addr_in_range(uint64_t offset);

void pfe_print_scsi_cmd(struct scsi_cmd *cmd);
void pfe_print_scsi_cdb(uint8_t *scb);
void pfe_print_header(pfe_io_header_t *header);

int pfe_log_io_req(struct scsi_cmd *cmd, uint64_t offset, uint64_t length, char *buf);
uint64_t pfe_split_io_log(int io_header_fd, int io_header_split_fd);

uint64_t pfe_get_io_cnt(int io_header_fd);
uint64_t pfe_replay_failure(int io_header_fd, int io_data_fd, int disk_fd, int fail_type, uint64_t start_id, uint64_t end_id, int err_blk_fd);

uint64_t pfe_do_normalwrite(int disk_fd, char *data_buf, uint64_t length, uint64_t offset);

void pfe_build_errblks_cache(int err_blk_fd);
void pfe_free_errblks_cache(void);

char * pfe_build_unser_pattern_cache(uint32_t * pattern_size);
void pfe_free_unser_pattern_cache(char * pattern_buf);

#endif

