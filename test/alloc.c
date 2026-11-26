#include "ubox.h"
#include <stdio.h>

int main() {

	LMM_NEW_POOL(buf0,64);
	ptr_t p;

	printf("max size: %d byte\n",64 * 4);

	if (!lmm_alloc(&p,buf0,sizeof(int))
}
