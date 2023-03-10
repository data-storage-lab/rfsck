#!/bin/sh

#
#
#   Copyright (c) International Business Machines  Corp., 2001
#
#   This program is free software;  you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY;  without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
#   the GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program;  if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#
#***********************************************************************
#
# TEST:
# 	NAME:		fs_inod
#	FUNCTIONALITY: 	File system stress - inode allocation/deallocation
# 	DESCRIPTION:	Rapidly creates and deletes files through
#			multiple processes running in the background.
#			The user may specify the number of subdirectories
#			to create, the number of files to create (per
#			subdirectory), and the number of times to repeat
#			the creation/deletion cycle.
#
#========================================================================
#
# CHANGE HISTORY:
# 		DATE            AUTHOR                  REASON
#       	04/18/98        Dara Morgenstein        Project Yeager (AIX)
#		02/08/01	Jay Inman		Modified to run standalone on Linux
#		05/24/01	Jay Inman		Added command line args
#		06/27/01	Jay Inman		Ported from Korn to Bash
#
#***********************************************************************


#=============================================================================
# FUNCTION NAME:        err_log
#
# FUNCTION DESCRIPTION: Log error
#
# PARAMETERS:           None.
#
# RETURNS:              None.
#=============================================================================
err_log()
{
    : $((step_errors += 1))
}


#=============================================================================
# FUNCTION NAME: 	make_subdirs
#
# FUNCTION DESCRIPTION: Creates $numsubdirs subdirectories
#
# PARAMETERS: 		None.
#
# RETURNS: 		None.
#=============================================================================
make_subdirs ()
{
    i=0;
    while [ "$i" -lt "$numsubdirs" ]; do
        [ -d dir$i ] || { \
            echo "$0: mkdir dir$i"
            mkdir -p dir$i || echo "mkdir dir$i FAILED"
        }
	: $((i += 1))
    done;
}


#=============================================================================
# FUNCTION NAME: 	touch_files
#
# FUNCTION DESCRIPTION: Creates $numfiles in each of $numsubdirs directories
#
# PARAMETERS: 		None.
#
# RETURNS: 		None.
#=============================================================================
touch_files()
{
    echo "$0: touch files [0-$numsubdirs]/file$numsubdirs[0-$numfiles]"
    j=0;

    while [ "$j" -lt "$numsubdirs" ]; do
	cd dir$j
	k=0;

	while [ "$k" -lt "$numfiles" ]; do
	    #>file$j$k || err_log ">file$j$k FAILED"
            < /dev/urandom tr -dc "[:alnum:]" | head -c 4096 > file$j$k || err_log ">file$j$k FAILED"
	    : $((k += 1))
	done

	: $((j += 1))
	cd ..
    done
}


#=============================================================================
# FUNCTION NAME: 	rm_files
#
# FUNCTION DESCRIPTION: Removes $numfiles in each $numsubdir directory
#
# PARAMETERS: 	None.
#
# RETURNS: 	None.
#=============================================================================
rm_files()
{
    echo "$0: rm files [0-$numsubdirs]/file$numsubdirs[0-$numfiles]"
    j=0;

    while [ "$j" -lt "$numsubdirs" ]; do
	cd dir$j
	k=0;

	while [ "$k" -lt "$numfiles" ]; do
	    rm -f file$j$k || err_log "rm -f file$j$k FAILED"
	    : $((k += 1))
	done

	: $((j += 1))
	cd ..
    done
}


#=============================================================================
# FUNCTION NAME: 	step1
#
# FUNCTION DESCRIPTION: multiple processes creating and deleting files
#
# PARAMETERS: 		None.
#
# RETURNS: 		None.
#=============================================================================
step1 ()
{
    echo "=============================================="
    echo "MULTIPLE PROCESSES CREATING AND DELETING FILES"
    echo "=============================================="

    echo "$0: creating dir2 subdirectories"
    [ -d dir2 ] || { \
        mkdir -p dir2 || end_testcase "mkdir dir2 failed"
    }
    cd dir2 || err_log "cd dir2 FAILED"
    make_subdirs || err_log "make_subdirs on dir2 FAILED"
    cd ..

    echo "$0: creating dir1 subdirectories & files"
    [ -d dir1 ] || { \
        mkdir dir1 || abort "mkdir dir1 FAILED"
    }
    cd dir1 || err_log "cd dir1 FAILED"
    make_subdirs || err_log "make_subdirs on dir1 FAILED"
    touch_files &
    pid1=$!

    i=1;
    while [ "$i" -le "$numloops" ]; do
	echo "Executing loop $i of $numloops..."

#	Added date stamps to track execution time and duration

	echo "$0: cd ../dir1 & creating files"
	cd ../dir1
	wait $pid1
	touch_files &
	pid1=$!

	echo "$0: cd ../dir1 & removing files"
	cd ../dir1
	wait $pid1
	rm_files &
	pid2=$!

	echo "$0: cd ../dir2 & creating files"
	cd ../dir2
	wait $pid2
	touch_files &
	pid2=$!

	echo "$0: cd ../dir2 & removing files"
	cd ../dir2
	wait $pid2
	rm_files &
	pid1=$!

	: $((i += 1))
    done

    # wait for all background processes to complete execution
    wait
    return $step_errors
}


#=============================================================================
# MAIN
#     See the description, purpose, and design of this test under TEST
#     in this test's prolog.
#=============================================================================
    USAGE="Usage: ./fs_inod [volumename] [numsubdirectories] [numfiles] [numloops]"

    if [ $# -ne 4 ]
    then
       echo $USAGE
       exit 2
    fi
    ERRORS=0

    testvol=$1
    numsubdirs=$2
    numfiles=$3
    numloops=$4

    cd $testvol || exit 2

    echo "FS_INODE: File system stress - inode allocation/deallocation"
    echo "Volume under test: $testvol"
    echo "Number of subdirectories: $numsubdirs"
    echo "Number of files: $numfiles"
    echo "Number of loops: $numloops"
    echo "Execution begins "
    date

    STEPS="1"
    for I in $STEPS
    do
         step_errors=0
         step$I
         if [ $? != 0 ]; then
            echo "step$I failed - see above errors"
            : $((ERRORS += step_errors))
         fi
    done

# Clean up and timestamp
    rm -rf $testvol/dir*
    echo "Execution completed"
    date

    exit $ERRORS
