#include <stdio.h>
#include <stdlib.h>
#include <print_string.h>

ssize_t print_string(int fd, char* str){
	ssize_t result = 0;
	FILE* fp = fdopen(fd, "a+");
	if(!fp)
	{
	  return ERROR;
	}
	result = fprintf(fp,str);
	fclose(fp);
	return result;
}
