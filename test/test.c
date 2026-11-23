#include "ubox.h"
#include <stdio.h>

#define PRINT_MSG(str,var) printf(str,var)

int main() {
	char buf[64];
	uint_t i;
	(void)str_size(&i,"Hello World",16);
	PRINT_MSG("len of \"Hello World\": %d\n",i);
	PRINT_MSG("string cmp: %d\n",str_equal("Hello","Hello World",4));
	(void)str_to_int(&i,"-2026",5);
	PRINT_MSG("number \"-2026\" : %d\n",i);
	int_to_str(buf,64,-234);
	PRINT_MSG("string -234: %s\n",buf);

	POOL_INIT(my,10,8);

	PRINT_MSG("pool limits: %d\n",POOL_READ_LIMIT(my[0]));
	PRINT_MSG("chunk size: %d\n",POOL_READ_CHUNK(my[0]));

	i = pool_free(my,1);

	printf("free status: %d\n",i);

	uint_t* p;

	i = pool_new(&p,my,1);
}
