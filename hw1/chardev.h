#ifndef CHARDEV_H
#define CHARDEV_H
#include<linux/ioctl.h>
#define MAJOR_NUM 1125
#define MINOR_NUM 1
#define DEVICE_FILE_DEST "/dev/char_dev"
#define DEVICE_FILE_NAME "char_dev"
typedef struct s_answer{ int number; char name[20]; }s_answer;

#endif
