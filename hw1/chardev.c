#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<linux/init.h>
#include "chardev.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("HyunSu");
#define SUCCESS 0
#define DEVICE_NAME "char_dev"
#define BUF_LEN 80
static int device_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
	printk(KERN_INFO "device_open(%p)\n", file);
	return SUCCESS;
}


static int device_release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	printk(KERN_INFO "device_release(%p,%p)\n", inode, file);
	return SUCCESS;
}


static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t * offset)
	{
		return SUCCESS;
	}
static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t * offset)
	{
		return SUCCESS;
	}
int device_ioctl(struct inode * inode, struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	s_answer * para;
	para = (s_answer *)ioctl_param;
	int s =0;
	struct task_struct *task = current;
//		put_user(task->comm,&(para[0].name));
	do
	{
		 copy_to_user(&(para[s].number),&(task->pid),4);
                copy_to_user(para[s].name,task->comm,20);
	s++;
		printk("durrent name : %s pid: %d\n",task->comm,task->pid);
		if(task->pid == 0)
			break;
		task=task->parent;
	}while(true);
	return SUCCESS;	
	

	/*
	int i=0;
	int npid=1;
	struct task_struct *p;
	struct pid *pid;
	rcu_read_lock();
	pid=find_get_pid(npid);
	p = pid_task(pid,PIDTYPE_PID);
	if(!p)
	{
	printk(KERN_INFO "error");
	return 0;
	}
	
	printk("virtual pid is %d\nglobal pid is %d\n",pid_vnr(p),pid_nr(p));
	//for(i=0;i <= (pid->level);i++)
	//	printk("[%d] %d\n",i,pid->numbers[i].nr);
	put_pid(pid);
    	rcu_read_unlock();
			
	//switch (ioctl_num) {
	//case IOCTL_PID:
	printk(KERN_INFO "success");
		//copy_to_user(*loctl_param,getpid(),sizeof(int));
	return SUCCESS;
	//}
*/

}


struct file_operations Fops = {
	
	.read = device_read,
	.write = device_write,
	.unlocked_ioctl = device_ioctl,
	.open = device_open,
	.release = device_release,	/* a.k.a. close */
};


int init_module(void)
{
	int ret_val;
	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);
	printk(KERN_INFO "init_module");
	if (ret_val < 0) {
		printk(KERN_ALERT "%s failed with %d\n",
		       "Sorry, registering the character device ", ret_val);
		return ret_val;
	}

	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "cleanup_module");
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}

