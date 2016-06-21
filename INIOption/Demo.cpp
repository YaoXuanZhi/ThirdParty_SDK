#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#include "IniReader.h"
#include "IniWriter.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>

void main()
{
	CIniWriter iniWriter(_T(".\\initest.ini"));
	iniWriter.WriteString(_T("GlobalSetting"), _T("PortFile"), _T("port.txt"));
	iniWriter.WriteString(_T("GlobalSetting"), _T("UrlFile"), _T("url.txt"));
	iniWriter.WriteString(_T("GlobalSetting"), _T("监听端口"), _T("8586"));
	iniWriter.WriteString(_T("GlobalSetting"), _T("检测间隔"), _T("10"));
	iniWriter.WriteString(_T("GlobalSetting"), _T("警报URL"), _T("http://hao123.com"));
	iniWriter.WriteString(_T("GlobalSetting"), _T("曲线阈值"), _T("10"));


	CIniReader iniReader(_T(".\\initest.ini"));
	LPTSTR szPortFile = iniReader.ReadString(_T("GlobalSetting"), _T("PortFile"), _T("port.txt"));
	LPTSTR szUrlFile = iniReader.ReadString(_T("GlobalSetting"), _T("UrlFile"), _T("url.txt"));
	LPTSTR szMonPort = iniReader.ReadString(_T("GlobalSetting"), _T("监听端口"), _T("8080"));
	LPTSTR szTimeOut = iniReader.ReadString(_T("GlobalSetting"), _T("检测间隔"), _T("1"));
	LPTSTR szWarnURL = iniReader.ReadString(_T("GlobalSetting"), _T("警报URL"), _T("http://baidu.com"));
	TCHAR szMaxFloatValue[255];
	iniReader.ReadString(_T("GlobalSetting"), _T("曲线阈值"), _T("1"), szMaxFloatValue);
	tcout << szPortFile << std::endl;
	tcout << szUrlFile << std::endl;
	tcout << szMonPort << std::endl;
	tcout << szTimeOut << std::endl;
	tcout << szWarnURL << std::endl;
	tcout << szMaxFloatValue << std::endl;

	delete szPortFile;
	delete szUrlFile;
	delete szMonPort;
	delete szTimeOut;
	delete szWarnURL;
	system("pause");
}


	
