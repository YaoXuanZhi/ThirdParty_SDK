#include <stdio.h>
#include <windows.h>
#include "regex.h"

char *sub_string(char *str, int start, int end)
{
	char * st = NULL;
	int i = start, j = 0;
	st = (char *)malloc(sizeof(char) * (end - start + 1));
	while (i < end) {
		st[j++] = str[i++];
	}
	st[j] = '\0';
	return st;
}

int main()
{
	regmatch_t pm[4];
	regex_t preg;
	char *pattern = "(href\\ *=\\ *\\\")([^\\\"]*)(\\\")"; //匹配串
	char *file = "<a href=\"http://www.awaysoft.com\">Awaysoft.com</a><a href=\"http://www.awaysoft2.com\">Awaysoft2.com</a><a href=\"http://www.awaysoft3.com\">Awaysoft.com3</a>", *st; //被匹配串

	if (regcomp(&preg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) { //编译正则表达式
		fprintf(stderr, "Cannot regex compile!");
		return -1;
	}
	st = file;

	while (st && regexec(&preg, st, 4, pm, REG_NOTEOL) != REG_NOMATCH) { //开始匹配
		printf("%s\n", sub_string(st, pm[2].rm_so, pm[2].rm_eo));
		st = &st[pm[3].rm_eo];//转到下一个匹配的初始位置
	}
	
	getchar();
	return 0;
}