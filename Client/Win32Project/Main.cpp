#include "Net/LoginHelper.h"
#include "Net/MainClient.h"
#include "Action.h"
#include "Net/Action/AcMainLogin.h"
#include "Net/Action/AcGetBuddies.h"
#include <stdio.h>
int main()
{
	Net::MainClient::Instance().GetACCreater()->Registe(Common::NETMSG_GETBUDDIES , &Net::AcGetBuddies::Create);
	Net::MainClient::Instance().GetACCreater()->Registe(Common::NETMSG_LOGINMAIN , &Net::AcMainLogin::Create);
	Net::LoginHelper lh;
	lh.Start(1);
	lh.Register("hhrt45h","1241215");
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