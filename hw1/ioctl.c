#include "chardev.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */


main()
{
	int file_desc, ret_val;
	int buf[256];
	char str[256];
	int k=0;
	s_answer answer[20];
	file_desc = open(DEVICE_FILE_DEST, 0);
	if (file_desc < 0) {
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}
	ioctl(file_desc,0,answer);
	while(1)
	{
	//	printf("%d\n",answer[k].number);
	//	printf("%s\n",answer[k].name);	
	if(answer[k].number==0)
		break;
	k++;
	}
	int e =0,j;
	while(k>=0)
	{
		printf("%s(%d)\n",answer[k].name,answer[k].number);
	
		if(k!=0)
		{for(j=0;j<e;j++)
			printf(" ");
		printf("\\-");
		}e++;
		k--;

	}


	close(file_desc);
}
