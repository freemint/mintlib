/*
 * Note that although this is provided in a separate file so that users
 * can say something like:
 *    long foo[800]; void *_heapbase = (void *)foo;
 * this is no longer necessary. (This used to be the idiom for desk
 * accessories, which need to have stack memory set aside for them;
 * but the acc startup code now Mallocs such memory automatically.)
 */

void *_heapbase = 0;	/* "0" means: heap not yet def'd. see crtinit.c */
