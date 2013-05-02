#include "Platform/platform.h"
#include <Windows.h>
std::string GetTime()
{
	SYSTEMTIME systime;
	::GetLocalTime(&systime);
	char localtime[256] = {0};
	sprintf(localtime,"%4d-%02d-%02d %02d:%02d:%02d",
		systime.wYear , systime.wMonth , systime.wDay , systime.wHour , systime.wMinute , systime.wSecond);
	return localtime;
}