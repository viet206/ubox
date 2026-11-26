#include "ubox.h"

int mem_copy(byte_t* restrict dst,byte_t* restrict src,uint_t size) {

	ptr_t d;
	ptr_t s;

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

	ptr_t d;

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

int lmm_alloc(ptr_t* restrict addr,ptr_t* restrict pool,uint_t size) {

	if ( addr == VOID || pool == VOID ) return FALSE;

	uint_t limit = pool->u[0];
	uint_t cur = pool->u[1];

	if ( cur + size > limit ) return FALSE;

	pool->u[cur] = size;
	addr =  &pool[cur + 1];

	return TRUE;
}

int pool_free(uint_t* restrict pool,int mode_clean) {

	if ( pool == VOID ) return FALSE;
	if ( pool[1] <= 0 ) return FALSE;

	int cur = pool[1];
	int size = pool[cur - 1];

	switch (mode_clean) {
		case LINEAR_FREE:
			cur -= size + 1;
			return TRUE;
		case LINEAR_CLEAN:
			cur -= size + 1;
			return TRUE;
		default:
			return FALSE;
	}
}
