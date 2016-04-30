#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <print_string.h>

ssize_t print_string(int fd, char* str){
	ssize_t result = 0;
	result = write(fd,str, strlen(str));
	if(result < 0)return ERROR;
	return result;
}
