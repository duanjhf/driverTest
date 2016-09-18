/*
 * netlinkDefine.h.
 * Description: netlinkDefine.h.
 * Author: duan. Created on: 2016年5月15日
 * copyright(c)2016. LICENSE("GPL/BSD")
 */

#ifndef INCLUDE_NETLINKDEFINE_H_
#define INCLUDE_NETLINKDEFINE_H_

typedef	char			int8;
typedef	short			int16;
typedef	int				int32;
typedef	unsigned char	uint8;
typedef	unsigned short	uint16;
typedef	unsigned int	uint32;

#define	NETLINK_DRIVER_TEST	(27)

typedef enum {
	NL_MSG_TYPE_PID,
} NL_MSG_TYPE;

#endif /* INCLUDE_NETLINKDEFINE_H_ */
