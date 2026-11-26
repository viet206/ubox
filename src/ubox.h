#ifndef MICRO_BOX_C_H
#define MICRO_BOX_C_H

#define __VERSION "0.0.9"

#define TRUE 1
#define FALSE 0
#define VOID (void*)0

#define LMM_NEW_POOL(name,max) \
	static uint_t name[max]; \
	name[0] = max; \
	name[1] = 2

typedef unsigned int uint_t;
typedef unsigned short uhalf_t;
typedef unsigned char byte_t;
typedef unsigned long long ull_t;

typedef union {
	uhalf_t* h;
	byte_t* b;
	ull_t* ll;
	uint_t* u;
}ptr_t;

typedef enum {
	LINEAR_FREE,
	LINEAR_CLEAN
}mode_clean;

int mem_copy(byte_t* restrict dst,byte_t* restrict src,uint_t size);
int mem_clear(byte_t* restrict mem,uint_t size);
int str_to_int(int* restrict result,const char* const number,uint_t len);
int str_length(uint_t* restrict result,const char* const s,uint_t max_size);
int str_equal(const char* const dst,const char* const src,uint_t n);
int int_to_str(char* restrict buf,uint_t size,int number);
const char* msg_to_str(int errcode);

#endif
