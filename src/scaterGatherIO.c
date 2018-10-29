/*
Example code to copy file from src file to dest file using scatter Gather IO
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <limits.h>
#include <errno.h>

//#define BUFF_SIZE (__IOV_MAX*PAGE_SIZE)
//#define __IOV_MAX 8

int main(int argc, char* argv[]){

	struct iovec readIov[__IOV_MAX];
	struct iovec writeIov[__IOV_MAX];
	ssize_t nr;
	int readFd, writeFd;
    long sz = sysconf(_SC_PAGESIZE);
    char *buff = (char *) malloc(sz * __IOV_MAX);
    
    printf("Page Size : %ld, __IOV_MAX: %d\n",sz,__IOV_MAX);

    /*Check if both src & dest files are received or --help is received to get usage*/
    if( (argc != 4) || !(strcmp(argv[1],"--help")) )    {
        printf("\nUsage: cpcmd source_file destination_file\n");
        exit(EXIT_FAILURE);
    }
    
    /*Open source file*/
    readFd = open(argv[1],O_RDONLY);
    if(readFd == -1)    {
        printf("\nError opening file %s errno = %d\n",argv[1],errno);
        exit(EXIT_FAILURE);
    }
    
    /*Open destination file with respective flags & modes
     O_CREAT & O_TRUNC is to truncate existing file or create a new file
     S_IXXXX are file permissions for the user,groups & others*/
    writeFd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    
    if(writeFd == -1)   {
        printf("\nError opening file %s errno = %d\n",argv[2],errno);
        exit(EXIT_FAILURE);
    }
    
    int nBuffSize = atoi(argv[3]);
    printf("Length per iov buff: %d\n",nBuffSize);
    if(nBuffSize > __IOV_MAX) {
        printf("\nNumber Of buffer can't be greater than 8 as num buffer req = %d\n",atoi(argv[2]));
        exit(EXIT_FAILURE);
    }	
    
   int loop,nbread,totalBlock, reminder;

   for(loop=0; loop<nBuffSize;loop++){
	   readIov[loop].iov_base = &buff[loop*sz];
	   readIov[loop].iov_len = sz;
   }	

   for(loop=0; loop<nBuffSize;loop++){
	   writeIov[loop].iov_base = readIov[loop].iov_base;
	   writeIov[loop].iov_len = sz;
   }

    while((nbread = readv(readFd,readIov,nBuffSize)) > 0)   {
        if(nbread != (nBuffSize * sz))        {
            totalBlock = nbread / sz;
            writeIov[totalBlock].iov_len = nbread%sz;
            nBuffSize = totalBlock+1;
        }
        if(writev(writeFd,writeIov,nBuffSize) != nbread)
            printf("\nError in writing data to %s\n",argv[2]);
    }
    
    if(nbread == -1)
        printf("\nError in reading data from %s\n",argv[1]);
    
    if(close(readFd) == -1)
        printf("\nError in closing file %s\n",argv[1]);
    
    if(close(writeFd) == -1)
        printf("\nError in closing file %s\n",argv[2]);
    free(buff);
exit(EXIT_SUCCESS);
}
