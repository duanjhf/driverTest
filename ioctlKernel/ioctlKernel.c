/*
 * ioctlKernel.c
 * Description: ioctl kernel test.
 * Author: duan. Created on: Apr 15, 2018
 * copyright(c)2018. LICENSE("GPL/BSD")
 */

#include <linux/init.h>
#include <linux/module.h>

#include "../include/dDefineKernel.h"


/************************************************************************************************/
/*                                      CONFIGURATIONS                                          */
/************************************************************************************************/
MODULE_LICENSE("Dual GPL/BSD");
MODULE_AUTHOR("duanjhf");
MODULE_DESCRIPTION("ioctl driver test.");

/************************************************************************************************/
/*                                        VARIABLES                                             */
/************************************************************************************************/

/************************************************************************************************/
/*                                        LOCAL FUNTIIONS                                       */
/************************************************************************************************/
static int ioctlKernelInit(void)
{
	kDebug("ioctl kernel init.");
	return 0;
}

static void ioctlKernelExit(void)
{
	kDebug("ioctl kernel exit.");
	return;
}

module_init(ioctlKernelInit);
module_exit(ioctlKernelExit);

/************************************************************************************************/
/*                                        PUBLIC FUNTIIONS                                      */
/************************************************************************************************/


