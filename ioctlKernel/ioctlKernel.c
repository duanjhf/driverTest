/*
 * ioctlKernel.c
 * Description: ioctl kernel test.
 * Author: duan. Created on: Apr 15, 2018
 * copyright(c)2018. LICENSE("GPL/BSD")
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>	/* copy_*_user */

#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */

#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/fs.h>

#include "../include/dDefineKernel.h"


/************************************************************************************************/
/*                                      CONFIGURATIONS                                          */
/************************************************************************************************/
MODULE_LICENSE("Dual GPL/BSD");
MODULE_AUTHOR("duanjhf");
MODULE_DESCRIPTION("ioctl driver test.");

/************************************************************************************************/
/*                                        DEFINE                                                */
/************************************************************************************************/
struct scull_dev {
	struct cdev cdev;	  /* Char device structure		*/
};

/************************************************************************************************/
/*                                        VARIABLES                                             */
/************************************************************************************************/
static unsigned int scull_major = 0;
static unsigned int scull_minor = 0;
static unsigned int scull_nr_devs = 4;

static struct scull_dev *scull_devices = NULL;

struct file_operations scull_fops = {
	.owner =    THIS_MODULE,
	.llseek =   NULL,
	.read =     NULL,
	.write =    NULL,
//	.ioctl =    NULL,
	.open =     NULL,
	.release =  NULL,
};

/************************************************************************************************/
/*                                        LOCAL FUNTIIONS                                       */
/************************************************************************************************/
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	dev_t dev_no = MKDEV(scull_major, scull_minor + index);
	int err = 0;

	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add(&dev->cdev, dev_no, 1);

	if (err) {
		kError("Error %d add cdev scull%d.", err, index);
	}
	return;
}


static void ioctlKernelExit(void)
{
	int i = 0;
	dev_t dev_no = MKDEV(scull_major, scull_minor);

	kDebug("ioctl kernel exit.");
	kDebug("scull dev no = %0#x, major = %0#x, minor = %0#x.", dev_no, scull_major, scull_minor);

	if (NULL != scull_devices) {
		for (i = 0; i < scull_nr_devs; ++ i) {
			cdev_del(&scull_devices[i].cdev);
		}
		kfree(scull_devices);
		scull_devices = NULL;
	}

	if (dev_no) {
		unregister_chrdev_region(dev_no, scull_nr_devs);
	}
	return;
}

static int ioctlKernelInit(void)
{
	int ret = 0;
	int i = 0;
	dev_t dev_no = 0;

	kDebug("ioctl kernel init.");

	ret = alloc_chrdev_region(&dev_no, scull_minor, scull_nr_devs, "scull");
	if (ret < 0) {
		kError("alloc sucll chrdev failed.");
		goto fail;
	}

	scull_major = MAJOR(dev_no);
	kDebug("sucll dev mjor = %0#x, minor = %0#x.", scull_major, scull_minor);

	scull_devices = kmalloc(scull_nr_devs * sizeof(struct scull_dev), GFP_KERNEL);
	if (NULL == scull_devices) {
		kError("alloc scull devices failed.");
		ret = -ENOMEM;
		goto fail;
	}

	for (i = 0; i < scull_nr_devs; ++ i) {
		scull_setup_cdev(&scull_devices[i], i);
	}

	return 0;

fail:
	ioctlKernelExit();
	return ret;
}



module_init(ioctlKernelInit);
module_exit(ioctlKernelExit);

/************************************************************************************************/
/*                                        PUBLIC FUNTIIONS                                      */
/************************************************************************************************/


