This is the repository for the "Towards Robust File System Checkers" project
published in the proceedings of the 16th USENIX Conference on File and Storage Technologies (FAST'18).

The repository contains the prototypes of the following:

  1. "rfsck-lib" contains the source files for rfsck-lib. 
      There is a README available in this folder with steps to
      show how to integerate the tool with your program
      
  2.  "rfsck-ext" is an example of how we integrated rfsck-lib with e2fsck. 
      The source files of the log file are copied into the folder 
      rfsck-ext/lib/ext2fs/. Then redo.h is imported into various header files. 
      
      A grep on the function names would show you how we have integrated 
      rfsck-lib with e2fsck.

      In this example we have provided safe transactions for all the updates
      in each pass.
      
  3.  "rfsck-xfs" is an example of how we integrated rfsck-lib with xfs_repair.
      Similar to rfsck-ext, we have copied the redo log files to folder 
      rfsck-ext/xfslib/, and then included redo.h into various header files.

      In this example we consider updates of the entire run of xfs_repair as
      one transaction
      
  4.  "e2fsck-patch" is a simple fix to make e2fsck robust. To achieve this,
      we synchronize the updates to the undo log.

  5.  "rfsck-test" is a  fault injection engine to analyze the fault resilience of file system checkers.


For further information about the design, please refer to our paper:
https://www.usenix.org/conference/fast18/presentation/gatla 


Contact: Om Rameshwar Gatla, omram@nmsu.edu
