/*
 *  FPGA read and write test program
 *  Version history:
 *	V1.0:2018-07-24 11:51:592018-07-24 11:51:59
 *	
 *  Copyright (C) 2009 
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
*/
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define COUNT 1 
#define BUF_SIZE 1024
#define DEVICE_FILE "/dev/ut"
//#define DEVICE_FILE "/mnt/aaa/git/bash-shell/driverOfLinux/xilinx_ram_driver/test.txt"
void help(void)
{
	printf("plm_write(char device read write test program) help:\n\
	plm_write [rw]	start_ops  count  write_start_char\n\
		max number is 1024\n\n\
		[rw]  read or write or all\n\
		start_ops >=0 (Bytes)\n\
		count >=0  \n\
		write_start_char is Ascii number \n\
		\n");	
	
}
int main(int argc, char *argv[])
{
	int fd;
	int num=0,i=0,j=COUNT,ti=0;
	int ws=1;
	char buf[BUF_SIZE];
	char temp;
	char itemp[BUF_SIZE]; 
	char wschar[8];
	char last[]="\0";
	int opn=0; /* opn :1->Read;2->Write;0->RWR; */
	int so=2; /* start-offset of args to read */
	int pcnt=0;
	
	if(argc < 3)
	{
		help();
		return -1;
	}

	if(argc == 4 || argc == 5)
	{
		if(*argv[1] == 'r'){
			opn=1;
			so=3;
			printf("Only Read\n");
		}

		else if((*argv[1] == 'w')&&(NULL != argv[4])){
			opn=2;
			so=3;
			printf("Only Write\n"); 
			ws=(atoi(argv[4]))?(atoi(argv[4])):1;	
		}else if(*argv[1] == 'w'){
			opn=2;
			so=3;
			printf("Only Write\n");
		}	
		else if(NULL != argv[3]){
			ws=(atoi(argv[3]))?(atoi(argv[3])):1;
		}

	}else
		help();
	
	if(opn == 0)
		printf("Read Write Read\n");
	
	fd = open(DEVICE_FILE, O_RDWR);
	if(fd < 0)
	{
		printf("open file error!\n");
		return -1;
	}

	if(NULL != argv[so] && so>=2 )
	{
		j=(atoi(argv[so]))?(atoi(argv[so])):COUNT;
		so--;
		ti=atoi(argv[so]);
		j+=ti;
	}
	
	if(opn==2)
		printf("ops Byte offset from %d to %d\n",ti,j);
	else	
		printf("ops Byte offset from %d to %d\n",2*ti,j);

	memset(buf, 0, BUF_SIZE);
	if(opn !=  2){
	/* 1. read firstly */		
		printf("Start Read\n");
		i=ti;
		/* seek unit is half-word(16bit) in ubuntu 14.04 */
		lseek(fd, i, SEEK_SET);
		num = read(fd, buf,j);
			
		for(i=ti,pcnt=2*ti;i<j;i++,pcnt++)
		{	
			printf("num[%d]Byte=%c=0x%x\n",pcnt,buf[i], (int)buf[i]);
		}
		if(opn == 1)
			return 0;
	}

	/* 2. write data to address */
	printf("\nStart Write\n\n");
	/*	set start value 	*/
	i=ti;
	lseek(fd, i, SEEK_SET); 
	
	for(;i<j;i++)
	{
		memset(wschar, 0, 8);
		sprintf(wschar,"%d",ws);
		strcat(itemp,wschar);
		ws++;
	}
	strcat(itemp,last);

	write(fd, itemp, strlen(itemp));
	if(opn == 2)
		return 0;

	/* 3. read lastly */
	i=ti;
	/* seek unit is half-word(16bit) in ubuntu 14.04 */
	lseek(fd, i, SEEK_SET);
	num = read(fd, buf,j);
		
	for(i=ti,pcnt=2*ti;i<j;i++,pcnt++)
	{	
		printf("AN[%d]Byte=%c=0x%x\n",pcnt,buf[i], (int)buf[i]);
	}
   

	return 0;
}

