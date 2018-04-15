/*
 * dDefineKernel.h
 * Description: 
 * Author: duan. Created on: Apr 15, 2018
 * copyright(c)2018. LICENSE("GPL/BSD")
 */


#ifndef INCLUDE_DDEFINEKERNEL_H_
#define INCLUDE_DDEFINEKERNEL_H_

/************************************************************************************************/
/*                                          DEFINES                                             */
/************************************************************************************************/
#define	kDebug(fmt, args...)	\
	printk("[kDebug] %d, %s: "fmt"\r\n", __LINE__, __FUNCTION__, ##args)
#define	kError(fmt, args...)	\
	printk("[!!!! kError] %d, %s: "fmt"\r\n", __LINE__, __FUNCTION__, ##args)

#endif /* INCLUDE_DDEFINEKERNEL_H_ */
