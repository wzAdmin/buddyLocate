#include "Net/LoginHelper.h"
#include "Net/MainClient.h"
#include <stdio.h>
int main()
{
	Net::LoginHelper lh;
	lh.Start(1);
	lh.Register("1267156","1241215");
	char c;
	while(c = getchar())
	{
		if('q'==c)
			break;
	}
	lh.Stop();
	Net::MainClient::Instance().Stop();
	return 0;
}