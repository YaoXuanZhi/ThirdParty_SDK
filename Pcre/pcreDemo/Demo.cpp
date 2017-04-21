#ifdef  __cplusplus  
extern "C" {  
#endif  
#include "../pcre/pcre-7.0-src/pcre.h"
#ifdef  __cplusplus  
}  
#endif  

#ifdef _DEBUG
#pragma comment(lib,"../Debug/pcre.lib")
#else
#pragma comment(lib,"../Release/pcre.lib")
#endif

#include <stdio.h>
#include <string.h>
#include "LeakDetector/LeakDetector.h"

#define OVECCOUNT 30    /* should be a multiple of 3 */
#define EBUFLEN 128
#define BUFLEN 1024


//������ʽר�������ж�ĳ���ַ����Ƿ����ĳ�ָ�ʽ
//ͨ�������ж�e-mail��ip��ַ��url���̻��ȳ�����ʽ
//���⣬Ҳ���Ը�Ч�طָ��ַ���
int main()
{
	EnableMemLeakCheck();
	pcre            *re;
	const char      *error;
	int             erroffset;
	int             ovector[OVECCOUNT];
	int             rc;
	//char            src    [] = "<head><title>Hello World</title></head>";
	//char            pattern   [] = "<title>(.*)</title>";
	//char* src="000.000.000.000";
	//char *src="127.aa0.a0a.c1c";
	//char *src="17.000.000.001";
	//char *pattern="(([01]?\\d?\\d|2[0-4]\\d|25[0-5])\\.){3}([01]?\\d?\\d|2[0-4]\\d|25[0-5])";
	//char *pattern="finance\\.sina\\.cn|stock1\\.sina\\.cn|3g\\.sina\\.com\\.cn.*(channel=finance|_finance$|ch=stock|/stock/)|dp.sina.cn/.*ch=9&";
	//char *src="finance.sina.cn/google.com/baidu.com.google.sina.cndddddddddddddddddddddda.sdfasdfeoasdfnahsfonadsdf";
	char          src    [] = "111 <title>Hello World</title> 222";
	char          pattern [] = "<title>(.*)</title>";
	printf("String : %s\n", src);
	printf("Pattern: \"%s\"\n", pattern);
	re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
	if (re == NULL) {
		printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
		system("pause");
		return 1;
	}

	rc = pcre_exec(re, NULL, src, strlen(src), 0, 0, ovector, OVECCOUNT);
	if (rc < 0) {
		if (rc == PCRE_ERROR_NOMATCH) printf("Sorry, no match ...\n");
		else    printf("Matching error %d\n", rc);
		free(re);
		system("pause");
		return 1;
	}
	printf("\nOK, has matched ...\n\n");

	//����ƥ����ַ���
	for( int i=0;i<rc;i++)
	{
		char* szSub_start=src+ovector[2*i];
		int iSubLen=ovector[2*i+1]-ovector[2*i];
		printf("%2d: %.*s\n", i, iSubLen, szSub_start);
	}

	free(re);
	system("pause");
	return 0;
}