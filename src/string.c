#include "ubox.h"

int str_to_int(int* restrict result,const char* const number,uint_t len) {

	if ( number == VOID ) return FALSE;
	if ( len < 1 ) return FALSE;
	if ( result == VOID ) return FALSE;

	for ( int i = 0 ; number[i] != '\0' ; i++ ) {
		if ( number[i] >= '0' && number[i] <= '9' ) *result = *result * 10 + ( number[i] - '0' );
	}

	if ( number[0] == '-' ) *result = -(*result);
	
	return TRUE;
}

int str_length(uint_t* restrict result,const char* const s,uint_t range) {
    uint_t len = 0;

	if ( s == VOID || result == VOID ) return FALSE;

	for ( ; len <= range ; len++ ) {
		if ( s[len] == '\0' ) break;
	}

	*result = len;

	return TRUE;
}

int str_equal(const char* const dst,const char* const src,uint_t n) {

	if ( dst == VOID || src == VOID ) return FALSE;

	for ( uint_t i = 0 ; i <= n ; i++ ) {
		if ( dst[i] != src[i] ) return FALSE;
    }

    return TRUE;
}

int int_to_str(char* restrict buf, uint_t size, int number) {
    uint_t i = 0;
    uint_t cur;
    int n = number;
    char tmp;

    if (buf == VOID || size == 0)
        return FALSE;

    // Xử lý số âm
    if (n < 0)
    {
        if (size < 2)
            return FALSE;

        buf[i++] = '-';
    }

    // Xử lý số INT_MIN an toàn
    unsigned int value = (n < 0) ? (unsigned int)(-(n + 1)) + 1
                                  : (unsigned int)n;

    // Trường hợp number = 0
    if (value == 0)
    {
        if (i + 1 >= size)
            return FALSE;

        buf[i++] = '0';
    }

    // Chuyển từng chữ số
    while (value > 0)
    {
        if (i + 1 >= size)
            return FALSE;

        buf[i++] = (value % 10) + '0';
        value /= 10;
    }

    // Đảo phần chữ số, giữ nguyên dấu âm
    cur = (n < 0) ? 1 : 0;

    uint_t left = cur;
    uint_t right = i - 1;

    while (left < right)
    {
        tmp = buf[left];
        buf[left] = buf[right];
        buf[right] = tmp;

        left++;
        right--;
    }

    buf[i] = '\0';

    return TRUE;
}

const char* msg_to_str(int errcode) {
    switch (errcode) {
        case TRUE: return "true";
        case FALSE: return "false";
        default: return "unknown";
    }
}
