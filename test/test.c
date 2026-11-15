#include "ubox.h"
#include <stdio.h>

#define PRINT_MSG(str,var) printf(str,var)

int main() {
	char buf[64];
	int i;
	PRINT_MSG("len of \"Hello World\": %d\n",str_size("Hello World",15));
	PRINT_MSG("string cmp: %d\n",str_equal("Hello","Hello World",4));
	str_to_int(&i,"-2026",5);
	PRINT_MSG("number \"-2026\" : %d\n",i);
	int_to_str(buf,64,-234);
	PRINT_MSG("string -234: %s",buf);
}
