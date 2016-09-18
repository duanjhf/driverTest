/*
 * netlinkKernel.c.
 * Description: netlinkKernel.c.
 * Author: duan. Created on: 2016年8月2日
 * copyright(c)2016. LICENSE("GPL/BSD")
 */

#include "../include/netlinkDefine.h"

#include <linux/init.h>
#include <linux/module.h>

#include <linux/sched.h>
#include <linux/timer.h>

#include <linux/netlink.h>
#include <net/sock.h>
#include <linux/skbuff.h>

/************************************************************************************************/
/*                                      CONFIGURATIONS                                          */
/************************************************************************************************/
MODULE_LICENSE("Dual GPL/BSD");
MODULE_AUTHOR("duanjhf");
MODULE_DESCRIPTION("netlink driver test.");

/************************************************************************************************/
/*                                          DEFINES                                             */
/************************************************************************************************/
#define	kDebug(fmt, args...)	\
	printk("[kDebug] %d, %s: "fmt, __LINE__, __FUNCTION__, ##args)
#define	kError(fmt, args...)	\
	printk("[!!!! kError] %d, %s: "fmt, __LINE__, __FUNCTION__, ##args)

/************************************************************************************************/
/*                                        VARIABLES                                             */
/************************************************************************************************/
struct sock *_nlSock;
uint32 _netlinkPid = 0;

/************************************************************************************************/
/*                                        LOCAL FUNTIIONS                                       */
/************************************************************************************************/
static void _nlRecvHandle(struct sk_buff *__skb)
{
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlH = NULL;

	skb = skb_get(__skb);
	if (NULL == skb) {
		kError("get skb is NULL.\r\n");
		return;
	}

	nlH = (struct nlmsghdr *)skb->data;
	kDebug("msg type = %d\r\n", nlH->nlmsg_type);

	kfree_skb(skb);
	skb = NULL;
	return;
}

//static int __init netlinkKernelInit(void)
static int netlinkKernelInit(void)
{
	struct netlink_kernel_cfg nlCfg = {
			.input = _nlRecvHandle,
	};

	_nlSock = netlink_kernel_create(&init_net, NETLINK_DRIVER_TEST, &nlCfg);
	if (NULL == _nlSock) {
		kDebug("netlink sock create failed.\r\n");
		return -1;
	}

	kDebug("netlink kernel iiiinit.\r\n");
	return 0;
}

//static void __exit netlinkKernelExit(void)
static void netlinkKernelExit(void)
{
	if (NULL != _nlSock) {
		netlink_kernel_release(_nlSock);
		_nlSock = NULL;
	}

	kDebug("netlink kernel eeeexit.\r\n");
	return;
}

module_init(netlinkKernelInit);
module_exit(netlinkKernelExit);

/************************************************************************************************/
/*                                        PUBLIC FUNTIIONS                                      */
/************************************************************************************************/
int nlSend(uint8 *buff, uint32 len, nl_msg_type_t msgType)
{
	int32 retval = -1;
	uint32 size = 0;
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlH = NULL;

	if (0 == )
}









