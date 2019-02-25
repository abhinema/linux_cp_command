# linux_cp_command

## Description:
try to mimic linux cp command and try to achieve linux performance
1. testcp.c : will use stdio apis (read from source & write to destnation).
2. scaterGatherIO.c : will use readv() and writev() api

Added helloworld code. 

## Profile and Run commands:
#### 1. time ./copy_sg <src_file> <dst_file> <BLK_SIZE>
#### 2. time ./copy_normal <src_file> <dst_file> <BLK_SIZE>
#### 3. ./helloworld 
to check if executable is getting created 
