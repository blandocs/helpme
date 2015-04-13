#include "msrdrv.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */


int main()
{
	int file_desc, ret_val, i,j;
	struct MsrInOut func[33];	
//disable		
	func[0].op =MSR_WRITE;
	func[0].eax=0x00;
	func[0].ecx=0x38f;
	func[0].edx =0x00;
//reset
	func[1].op=MSR_WRITE;
	func[1].eax=0x00;
	func[1].ecx=0xc1;
	func[1].edx=0x00;
	
	func[2].op=MSR_WRITE;
	func[2].eax=0x00;
	func[2].ecx=0xc2;
	func[2].edx=0x00;
	
	func[3].op=MSR_WRITE;
	func[3].eax=0x00;
	func[3].ecx=0xc3;
	func[3].edx=0x00;
	
	func[4].op=MSR_WRITE;
	func[4].eax=0x00;
	func[4].ecx=0xc4;
	func[4].edx=0x00;


	
//let's enable
	func[7].op=MSR_WRITE;
	func[7].eax=0x0f;
	func[7].ecx=0x38f;
	func[7].edx=0x07;
//let's enable
	func[6].op=MSR_WRITE;
	func[6].eax=0x222;
	func[6].ecx=0x38d;
	func[6].edx=0x00;
//wrmsr start
	func[5].op=MSR_WRITE;
	func[5].eax=0x0041010e;
	func[5].ecx=0x187;
	func[5].edx=0x00;

	//func[8].op=MSR_RDTSC;
	for(j=8;j<=26;j++)
		func[j].op =MSR_NOP;


	func[27].op=MSR_READ;
	func[27].ecx=0xc1;
	
	func[28].op=MSR_READ;
	func[28].ecx=0xc2;

	func[29].op=MSR_READ;
	func[29].ecx=0xc3;


	func[30].op=MSR_READ;
	func[30].ecx=0xc4;


	func[31].op=MSR_RDTSC;

	func[32].op=MSR_READ;
	func[32].ecx=0xc1;

	

	file_desc = open(DEV_NAME,O_RDWR);
	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEV_NAME);
		exit(-1);
	}
	
	printf("before wrmsr: eax=0x%x, ecx=0x%x\n",func[2].eax,func[2].ecx);
	ioctl(file_desc,IOCTL_MSR_CMDS,func);
	printf("current time stamp: %lld\n",func[0].value );
	printf("after wrmsr: eax=0x%x, ecx=0x%x\n",func[2].eax,func[2].ecx);
	printf("Start count UOPS_ISSUED.ANY\n");
	printf("delay by access an array(27 nop)\n");
	printf("rdmsr: ecx=0x%x\n",func[30].ecx);
	printf("rdmsr: UOP_ISSUED.ANY is\n c1: %lld\n c2: %lld\n c3:%lld\n c4: %lld\n",func[27].value,func[28].value,func[29].value,func[30].value);
	printf("time stamp : %lld\n",func[31].value-func[8].value);
	//for(i=0;i<=32;i++)
	//	printf("op: %d, %lld\n",func[i].op,func[i].value);

	close(file_desc);
}
