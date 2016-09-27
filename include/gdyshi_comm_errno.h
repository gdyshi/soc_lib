/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: errno.h
 * 
 * Description:  
 * - This file implements the follow functions:
 * - 
 * 
 * Author: gdyshi 
 * Date:  13:28pm, 26.Jun.2012
 * Modification History
 * --------------------
 * Date              Modifier    Problem N.O.                 Description
 * --------------------
 ******************************************************************************/
#ifndef _GDYSHI_COMM_ERRNO_H_
#define _GDYSHI_COMM_ERRNO_H_


#define GDYSHI_SUCCESS	(0)

#define	GDYSHI_EPERM		 (-1)	/* Operation not permitted */
#define	GDYSHI_ENOENT		 (-2)	/* No such file or directory */
#define	GDYSHI_ESRCH		 (-3)	/* No such process */
#define	GDYSHI_EINTR		 (-4)	/* Interrupted system call */
#define	GDYSHI_EIO		     (-5)	/* I/O error */
#define	GDYSHI_ENXIO		 (-6)	/* No such device or address */
#define	GDYSHI_E2BIG		 (-7)	/* Argument list too long */
#define	GDYSHI_ENOEXEC		 (-8)	/* Exec format error */
#define	GDYSHI_EBADF		 (-9)	/* Bad file number */
#define	GDYSHI_ECHILD		(-10)	/* No child processes */
#define	GDYSHI_EAGAIN		(-11)	/* Try again */
#define	GDYSHI_ENOMEM		(-12)	/* Out of memory */
#define	GDYSHI_EACCES		(-13)	/* Permission denied */
#define	GDYSHI_EFAULT		(-14)	/* Bad address */
#define	GDYSHI_ENOTBLK		(-15)	/* Block device required */
#define	GDYSHI_EBUSY		(-16)	/* Device or resource busy */
#define	GDYSHI_EEXIST		(-17)	/* File exists */
#define	GDYSHI_EXDEV		(-18)	/* Cross-device link */
#define	GDYSHI_ENODEV		(-19)	/* No such device */
#define	GDYSHI_ENOTDIR		(-20)	/* Not a directory */
#define	GDYSHI_EISDIR		(-21)	/* Is a directory */
#define	GDYSHI_EINVAL		(-22)	/* Invalid argument */
#define	GDYSHI_ENFILE		(-23)	/* File table overflow */
#define	GDYSHI_EMFILE		(-24)	/* Too many open files */
#define	GDYSHI_ENOTTY		(-25)	/* Not a typewriter */
#define	GDYSHI_ETXTBSY		(-26)	/* Text file busy */
#define	GDYSHI_EFBIG		(-27)	/* File too large */
#define	GDYSHI_ENOSPC		(-28)	/* No space left on device */
#define	GDYSHI_ESPIPE		(-29)	/* Illegal seek */
#define	GDYSHI_EROFS		(-30)	/* Read-only file system */
#define	GDYSHI_EMLINK		(-31)	/* Too many links */
#define	GDYSHI_EPIPE		(-32)	/* Broken pipe */
#define	GDYSHI_EDOM		    (-33)	/* Math argument out of domain of func */
#define	GDYSHI_ERANGE		(-34)	/* Math result not representable */

#endif /* _GDYSHI_COMM_ERRNO_H_ */
/*----------------------------------END OF FILE errno.h-------------------------------*/
