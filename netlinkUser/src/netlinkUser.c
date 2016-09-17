/*
 * netlinkUser.c.
 * Description: netlinkUser.c.
 * Author: duan. Created on: 2016年5月15日
 * copyright(c)2016. LICENSE("GPL/BSD")
 */

#include "netlinkUserDefine.h"
#include "netlinkDefine.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/************************************************************************************************/
/*                                        DEFINES                                               */
/************************************************************************************************/
#define	NETLINK_DRIVER_TEST	(27)

/************************************************************************************************/
/*                                        VARIABLES                                             */
/************************************************************************************************/
static int32 _netlinkFd = -1;

/************************************************************************************************/
/*                                    Local Functions                                           */
/************************************************************************************************/
static int _netlinkSend(NL_MSG_TYPE msgType, uint8 *data, uint32 dataLen)
{
	int retval					= -1;
	struct sockaddr_nl nlAddr	= {0};
	struct nlmsghdr *nlHdr		= NULL;
	uint8 *packetData			= NULL;
	uint32 packetSize			= 0;

	if (_netlinkFd < 0) {
		nlError("netlink socket is not init.\r\n");
		return -1;
	}

	memset(&nlAddr, 0, sizeof(nlAddr));
	nlAddr.nl_family = AF_NETLINK;
	nlAddr.nl_pid = 0;
	nlAddr.nl_groups = 0;
	nlAddr.nl_pad = 0;

	if (NULL != data) {
		nlDebug("msgType = %d, dataLen = %d.\r\n", msgType, dataLen);
		packetSize = NLMSG_SPACE(dataLen);
	} else {
		packetSize = NLMSG_SPACE(0);
	}
	nlHdr = (struct nlmsghdr *)malloc(packetSize);
	if (NULL == nlHdr) {
		nlError("malloc nlmsghdr failed.\r\n");
		return -1;
	}
	memset(nlHdr, 0, packetSize);
	nlHdr->nlmsg_len = packetSize;
	nlHdr->nlmsg_pid = getpid();
	nlHdr->nlmsg_type = msgType;
	nlHdr->nlmsg_flags = 0;

	/* data to driver. */
	if (NULL != data) {
		packetData = NLMSG_DATA(nlHdr);
		memcpy(packetData, data, dataLen);
	}

	retval = sendto(_netlinkFd, nlHdr, packetSize, 0, (struct sockaddr *)&nlAddr, sizeof(nlAddr));
	if (retval != packetSize) {
		nlError("send msg type %d to driver failed.\r\n", msgType);
		goto netlink_send_errr;
	}

	free(nlHdr);
	nlHdr = NULL;
	nlDebug("send %d Bytes to driver.\r\n", retval);
	return retval;

netlink_send_errr:
	if (NULL != nlHdr) {
		free(nlHdr);
		nlHdr = NULL;
	}
	return -1;
}

/************************************************************************************************/
/*                                    Public Functions                                          */
/************************************************************************************************/
int netlinkUserInit(void)
{
	int32 retval				= -1;
	struct sockaddr_nl nlAddr	= {0};
	static uint8 sendPidFlag	= 0;

	if (_netlinkFd >= 0) {
		if (0 == sendPidFlag) {
			/* send pid to kernel */
			_netlinkSend(NL_MSG_TYPE_PID, NULL, 0);
			sendPidFlag = 1;
		}
		return _netlinkFd;
	}

	_netlinkFd = socket(AF_NETLINK, SOCK_RAW, NETLINK_DRIVER_TEST);
	if (_netlinkFd < 0) {
		nlError("netlink socket init failed.\r\n");
		return -1;
	}

	memset(&nlAddr, 0, sizeof(AF_NETLINK));
	nlAddr.nl_family = AF_NETLINK;
	nlAddr.nl_pid = getpid();
	nlAddr.nl_groups = 0;
	nlAddr.nl_pad = 0;
	retval = bind(_netlinkFd, (struct sockaddr *)&nlAddr, sizeof(nlAddr));
	if (-1 == retval) {
		nlError("bind netlink socket failed.\r\n");
		goto netlinkInitErr;
	}

	if (0 == sendPidFlag) {
		/* send pid to kernel */
		_netlinkSend(NL_MSG_TYPE_PID, NULL, 0);
		sendPidFlag = 1;
	}

	nlDebug("init netlink successed, fd = %d\r\n", _netlinkFd);
	return _netlinkFd;

netlinkInitErr:
	close(_netlinkFd);
	_netlinkFd = -1;
	return -1;
}

void netlinkUserDeinit(void)
{
	if (_netlinkFd >= 0) {
		close(_netlinkFd);
		_netlinkFd = -1;
	}
	return;
}






