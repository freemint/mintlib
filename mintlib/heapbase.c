/*
 * Note that although this is provided in a separate file so that users
 * can say something like:
 *    long foo[800]; void *_heapbase = (void *)foo;
 * this is no longer necessary. (This used to be the idiom for desk
 * accessories, which need to have stack memory set aside for them;
 * but the acc startup code now Mallocs such memory automatically.)
 */

/* from crtinit.c:
 * set to heap base addr when _stksize < 0 || _initial_stack || When DA
 * note that we allow the user to provide a _heapbase of their own, since
 * that used to be necessary for acc's; but that is no longer needed
 * (or encouraged) since the acc startup code now Mallocs a heap
 * automatically
 */
void *_heapbase = 0;	/* "0" means: heap not yet def'd. see crtinit.c */
