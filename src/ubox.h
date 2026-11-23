#ifndef MICRO_BOX_C_H
#define MICRO_BOX_C_H

#define __VERSION "0.0.9"

#define TRUE 1
#define FALSE 0
#define VOID (void*)0

typedef unsigned int uint_t;
typedef unsigned short uhalf_t;
typedef unsigned char byte_t;
typedef unsigned long long ull_t;

typedef union {
	uhalf_t* h;
	byte_t* b;
	ull_t* ll;
}r21_t;

int mem_copy(byte_t* restrict dst,byte_t* restrict src,uint_t size);
int mem_clear(byte_t* restrict mem,uint_t size);
int str_to_int(int* restrict result,const char* const number,uint_t len);
int str_size(uint_t* restrict result,const char* const s,uint_t max_size);
int str_equal(const char* const dst,const char* const src,uint_t n);
int int_to_str(char* restrict buf,uint_t size,int number);
char* msg_to_str(int errcode);

#define POOL_READ_LIMIT(mt) (( mt >> 24 ) & 0xFF )
#define POOL_READ_CHUNK(mt) (( mt >> 8 ) & 0xFFFF )
#define POOL_READ_CUR(mt) ( mt & 0xFF )

#define POOL_WRITE_LIMIT(mt) (( mt & 0xFF ) << 24 )
#define POOL_WRITE_CHUNK(mt) (( mt & 0xFFFF ) << 8 )
#define POOL_WRITE_CUR(mt) ( mt & 0xFF )

#define POOL_INIT(buf,max,chunk) \
	uint_t buf[max]; \
	buf[0]= POOL_READ_CHUNK(chunk) | \
			POOL_READ_CUR(0) | \
			POOL_READ_LIMIT(max)

int pool_new(uint_t** restrict addr,uint_t* restrict pool,uint_t chunk);
int pool_free(uint_t* restrict pool,int mode);

#endif
