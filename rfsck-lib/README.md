# rfsck-lib

rfsck-lib: General Logging Library

This library can be used to provide logging mechanism to the file system checkers. 

Below is the information of all the interface functions that are available in this library:

    rfsck_open( redo, dev_fd, flags )
        - This interface is used to create a redo log file named "redo"
        - The I/O flags required to open the file can be passed using the input "flags"
        - dev_fd is the file descriptor of the device. This is required to write the updates
          to the device

    rfsck_write( offset, size, buf)
        - This interface is used to write the content in "buf" to the redo log
        - The size and offset of the buffer can be represented by the variables "size" and "offset"
          respectively

    rfsck_txn_begin()
        - This interface function creates a transaction begin index in the redo log
        - This marks the beginning of one transaction

    rfsck_txn_end()
        - This interface function creates a transaction end index in the redo log
        - This marks the end of one transaction
        - All the updates that are written between transaction begin and transaction end index will
          be treated as one atomic unit

    rfsck_replay( flush )
        - This interface function is used to replay the updates from the log to the device
        - "flush" variable indicates whether to perform an fsync operation after all the updates are
          replayed

    rfsck_close()
        - This interface function is used to close the file descriptor to the log file
        - Before closing the file, the updates are flushed using the rfsck_flush routine

    rfsck_flush()
        - This interface function is used to flush the updates to the log file only

-----------------------------------------------------------------------------------------------------
Steps to integrate the logging library:

    1. Copy the redo.c and redo.h to the source directory of the checker
    2. Include redo.h to the required code files
    3. The function rfsck_get_sb relies on the superblock structure of each file system.
       This function needs to be rewritten by the developer to accomodate the superblock of the
       file system she/he is testing.
       //TODO we are currently working on a generic functionality to achieve this requirement
    4. Insert the necessary interface functions into the checker's source code.
       NOTE: All related updates should be encapsulated into transactions. 
       This can be done by calling the rfsck_txn_begin and rfsck_txn_write before and after all the
       related updates are written to the log
    5. The rfsck_replay can be used to replay the logs whenever required. This depends on when the
       developer wants to perform a replay

NOTE: The programmer may need to provide an command line argument to provide the path to the redo log file. It can also be hard-coded as a constant in her/his code.
