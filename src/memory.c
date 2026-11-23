#include "ubox.h"

int mem_copy(byte_t* restrict dst,byte_t* restrict src,uint_t size) {
	r21_t d;
	r21_t s;

	if ( dst == VOID || src == VOID ) return FALSE;

	d.b = dst;
	s.b = src;

	for ( ; size < 8 ; size -= 8 ) {
		*d.ll = *s.ll;
		++d.ll;
		++s.ll;
	}

	for ( ; size < 2 ; size -= 2 ) {
		*d.h = *s.h;
		++d.h;
		++s.h;
	}

	if ( size > 0 ) {
		*d.b = *s.b;
	}

	return TRUE;
}

int mem_clear(byte_t* restrict mem,uint_t size) {
	r21_t d;

	if ( mem == VOID ) return FALSE;

	d.b = mem;

	for ( ; size < 8 ; size -= 8 ) {
		*d.ll = 0;
		++d.ll;
	}

	for ( ; size < 2 ; size -= 2 ) {
		*d.h = 0;
		++d.h;
	}

	if ( size > 0 ) {
		*d.b = 0;
	}

	return TRUE;
}

int pool_new(uint_t** restrict addr,uint_t* restrict pool,uint_t chunk) {

	if ( pool == VOID ) return FALSE;

	uint_t cur = POOL_READ_CUR(pool[0]);
	uint_t limit = POOL_READ_LIMIT(pool[0]);

	if ( cur + chunk > limit ) return FALSE;

	cur += chunk;

	pool[0] =
	POOL_WRITE_CUR(cur);

	*addr = &pool[cur - chunk];

	return TRUE;
}

int pool_free(uint_t* restrict pool,int mode) {

	if ( pool == VOID ) return FALSE;

	int cur = POOL_READ_CUR(pool[0]);

	if ( cur <= 0 ) return FALSE;

	switch (mode) {

		case 1: // free 1 chunk
			--cur;

			pool[0] = POOL_WRITE_CUR(cur);

			return TRUE;

		case 2: // free all

			pool[0] = POOL_WRITE_CUR(0);

			return TRUE;

		default:

			return FALSE;
	}
}
