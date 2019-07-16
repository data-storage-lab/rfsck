## rfsck-lib: Generic Redo Log Library ##
This repository consists of the source code for a generic redo log, which can be easily integrated to existing file system checkers to provide logging mechanism and make them fault resilient. We have published our paper titled **"Towards Robust File System Checkers"** at FAST'18, and it contains detailed information about the analysis and implementation of rfsck-lib.
[[Paper PDF](https://www.usenix.org/conference/fast18/presentation/gatla)]

In addition to the source code we also provide the following prototypes in this repo:

  1. **rfsck-ext** is an example of how we integrated rfsck-lib with e2fsck. 
      The source files of the log file are copied into the folder 
      rfsck-ext/lib/ext2fs/. Then redo.h is imported into various header files. 
      
      A grep on the function names would show you how we have integrated 
      rfsck-lib with e2fsck.

      In this example we have provided safe transactions for all the updates
      in each pass.
      
  2.  **rfsck-xfs** is an example of how we integrated rfsck-lib with xfs_repair.
      Similar to rfsck-ext, we have copied the redo log files to folder 
      rfsck-ext/xfslib/, and then included redo.h into various header files.

      In this example we consider updates of the entire run of xfs_repair as
      one transaction
      
  3.  **e2fsck-patch** is a simple fix to make e2fsck robust. To achieve this,
      we synchronize the updates to the undo log.

## rfsck-test: Fault Injection Framework ## 
To test the resilience of rfsck-lib, we use a fault injection framework that records iSCSI commands to the block device and replays prefix commands back to the device to emulate fault.



## Contact ## 
For any questions or issues please send an email to ogatla@iastate.edu
