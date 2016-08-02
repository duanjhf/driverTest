/*
 * netlinkUserDefine.h.
 * Description: netlinkUserDefine.h.
 * Author: duan. Created on: 2016年5月15日
 * copyright(c)2016. LICENSE("GPL/BSD")
 */

#ifndef NETLINKUSER_INCLUDE_NETLINKUSERDEFINE_H_
#define NETLINKUSER_INCLUDE_NETLINKUSERDEFINE_H_

extern char *basename(char *path);
#define	nlDebug(fmt, args...)	\
	printf("[nlDebug] %s, %d, %s: "fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)
#define	nlError(fmt, args...)	\
	printf("[!!!! nlError] %s, %d, %s: "fmt, basename(__FILE__), __LINE__, __FUNCTION__, ##args)

#endif /* NETLINKUSER_INCLUDE_NETLINKUSERDEFINE_H_ */
