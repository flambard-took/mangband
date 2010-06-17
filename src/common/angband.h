/* File: angband.h */

/* Main "Angband" header file */

#ifndef INCLUDED_ANGBAND_H
#define INCLUDED_ANGBAND_H

/*
 * Copyright (c) 1989 James E. Wilson
 *
 * This software may be copied and distributed for educational, research, and
 * not for profit purposes provided that this copyright and statement are
 * included in all such copies.
 */



/*
 * First, include the low-level includes.  Be sure to edit "h-config.h"
 * to reflect any hardware, operating system, or compiler nuances.
 */
#include "../common/h-basic.h"


/*
 * Then, include the header files for the low-level code
 */
#include "../common/z-util.h"
#include "../common/z-virt.h"
#include "../common/z-form.h"
#include "../common/z-rand.h"

#ifdef CLIENT
#include "../client/z-term.h"
#endif


/*
 * Include the "Angband" configuration header
 */
#include "../options.h"


/*
 * Now, include the define's, the type's, and the extern's
 *
 * Note that the externs are NOT common.
 */
#include "../common/defines.h"
#include "../common/net-basics.h"
#include "../common/types.h"
#ifdef CLIENT
#include "../client/c-defines.h"
#include "../client/c-externs.h"
#else
#include "../server/mdefines.h"
#include "../server/externs.h"
#endif



/***** Some copyright messages follow below *****/

/*
 * Note that these copyright messages apply to an ancient version
 * of Angband, as in, from pre-2.4.frog-knows days, and thus the
 * reference to "5.0" is rather misleading...
 */

/*
 * UNIX ANGBAND Version 5.0
 */


/* Original copyright message follows. */

/*
 * ANGBAND Version 4.8	COPYRIGHT (c) Robert Alan Koeneke
 *
 *	 I lovingly dedicate this game to hackers and adventurers
 *	 everywhere...
 *
 *	 Designer and Programmer:
 *		Robert Alan Koeneke
 *		University of Oklahoma
 *
 *	 Assistant Programmer:
 *		Jimmey Wayne Todd
 *		University of Oklahoma
 *
 *	 Assistant Programmer:
 *		Gary D. McAdoo
 *		University of Oklahoma
 *
 *	 UNIX Port:
 *		James E. Wilson
 *		UC Berkeley
 *		wilson@ernie.Berkeley.EDU
 *		ucbvax!ucbernie!wilson
 */


/*
 *	 ANGBAND may be copied and modified freely as long as the above
 *	 credits are retained.	No one who-so-ever may sell or market
 *	 this software in any form without the expressed written consent
 *	 of the author Robert Alan Koeneke.
 */


#endif
