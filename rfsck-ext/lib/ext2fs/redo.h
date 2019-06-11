
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

//#include "crc32defs.h"
#include "crc32c_defs.h"

#define REDO_HEADER_MAGIC_NUMBER "E2REDO01"
#define REDO_BLOCK_MAGIC_NUMBER  "E2REDO02"

#define E2REDO_STATE_FINISHED   0x1

#define BLK_TAG_REPLAYED 0x1

#define TXN_CHKSM_CNST 0x3F921710
#define TXN_REPLAYED_CNST 0x2FC8310A
struct redo_header {
  char     magic[8];          /* "E2REDO01" */
  uint64_t num_keys;        /* how many keys? */ // Not required - Commit block marks end of transaction
  uint64_t super_offset;    /* where in the file is the superblock copy? */ //TODO 
  uint64_t key_offset;      /* where do the key/data block chunks start? */
//  __le32 block_size;      /* block size of the undo file */
//  __le32 fs_block_size;   /* block size of the target device */
  uint32_t sb_crc;          /* crc32c of the superblock */                  //TODO
  uint32_t state;           /* e2redo state flag - set to 1 to after all blocks flushed to redo log */
  //__le32 f_compat;        /* compatible features */
  //__le32 f_incompat;      /* incompatible features (none so far) */
  //__le32 f_rocompat;      /* ro compatible features (none so far) */
//  __le32 pad32;           /* padding for fs_offset */
//  __le64 fs_offset;       /* filesystem offset */
  uint32_t header_crc;      /* crc32c of this header (but not this field) */
  uint8_t   padding[468];    /* padding */
};

struct redo_block_tag {
  uint64_t  offset;               // offset in block dev
  uint32_t  size;                // Size in bytes
//  __le32 replayed;
  uint32_t blk_crc;

};

struct redo_block {
  uint32_t magic;
  uint32_t crc;
  uint64_t reserved;

  struct redo_block_tag tags[];
};

/*struct rfsck_txn {
    //TODO
    int txn_id;
    int txn_begin_blk;
    int txn_begin_idx;
    int txn_end_blk;
    int txn_end_idx;

};*/

struct redo_private_data {
  // variables related to redo file
  char* redo_file;
  int   redo_fd;
  int   dev_fd;

  int tdb_written;

  // variables for read/write
  uint32_t redo_block_size;
  uint32_t dev_block_size;

  uint64_t num_keys;		// number of redo_blocks
  uint64_t redo_blk_num;  	// total number of blocks used in redo log
  uint64_t keys_in_block;
  uint64_t redo_block_offset;     // offset of current redo_block

  uint64_t log_offset;  

  // variables for redo log
  struct redo_header hdr;
  struct redo_block  *keyb;

  // variables for transaction support
  int txn_begin_blk;
  int txn_begin_idx;
  int txn_id;
  uint32_t txn_csum;
  //struct redo_block *blocks;
  
};
struct replay_block {
  uint32_t magic;
  uint32_t crc;
  uint64_t reserved;

  struct redo_block_tag tags[255]; // Change array size based on KEYS_PER_BLOCK
};
//#define REDO_LOG_BLOCK_SIZE 1024
#define REDO_LOG_BLOCK_SIZE   4096 // Change the array size in replay block based on KEYS_PER_BLOCK
#define KEYS_PER_BLOCK(d) (((d)->redo_block_size / sizeof(struct redo_block_tag)) - 1)
//struct redo_block replay_blocks[];
struct redo_private_data *redo_data;
//char *redo_file;
int rfsck_txn_begin();
int rfsck_txn_end();
int rfsck_open(char *redo, int dev_fd, int flags);
int rfsck_close();
int rfsck_write(uint64_t offset, uint32_t size, void* buf);
int rfsck_replay(int flush);
int redo_mark_done(int mark_done);
int rfsck_flush();
