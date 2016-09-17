/*
 * driverInstance.c.
 * Description: driverInstance.c.
 * Author: duan. Created on: 2016年5月15日
 * copyright(c)2016. LICENSE("GPL/BSD")
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

/************************************************************************************************/
/*                                      CONFIGURATIONS                                          */
/************************************************************************************************/
MODULE_LICENSE("Dual GPL/BSD");
MODULE_AUTHOR("duanjhf");
MODULE_DESCRIPTION("kernel && driver test.");

/************************************************************************************************/
/*                                          DEFINES                                             */
/************************************************************************************************/
#define	kDebug(fmt, args...)	\
	printk("[kDebug] %d, %s: "fmt, __LINE__, __FUNCTION__, ##args)

/************************************************************************************************/
/*                                        VARIABLES                                             */
/************************************************************************************************/
static struct timer_list _cycTimer;

/************************************************************************************************/
/*                                        LOCAL FUNTIIONS                                       */
/************************************************************************************************/
static void _cycTimerHandler(void)
{
	static unsigned int cnt = 0;

	++ cnt;
	kDebug("cyc timer handler. cnt = %u, jiffies = %ld\r\n", cnt, jiffies);
	mod_timer(&_cycTimer, jiffies + 5 * HZ);
	return;
}

static int __init driverTestInit(void)
{
	kDebug("driver test iiiinit.\r\n");

	/* init timer. */
	init_timer(&_cycTimer);
	_cycTimer.function = _cycTimerHandler;
	_cycTimer.expires = jiffies + 5 * HZ;
	add_timer(&_cycTimer);
	return 0;
}

static void __exit driverTestExit(void)
{
	kDebug("driver test eeeexit.\r\n");
	del_timer(&_cycTimer);
	return;
}

module_init(driverTestInit);
module_exit(driverTestExit);

/************************************************************************************************/
/*                                        PUBLIC FUNTIIONS                                      */
/************************************************************************************************/


