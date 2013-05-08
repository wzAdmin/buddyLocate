#include "DB/LoginDB.h"
#include "Net/LoginService.h"
#include "Net/MainServer.h"
#include "Action.h"
#include "Net/Action/ACGetBuddy.h"
#include "Net/Action/LoginMain.h"
#include "Net/Action/ACUploadGps.h"
#include "Net/Action/ACUploadContacts.h"
#include <stdio.h>

int main()
{
	Net::LoginService::Instance().Start(Net::LoginService::MaxConnectionNum , Net::LoginService::Port);
	Net::MainServer::Instance().Start(Net::MainServer::MaxConnectionNum , Net::MainServer::Port);

	Net::MainServer::Instance().GetACCreater()->Registe(Common::NETMSG_LOGINMAIN , &Net::LoginMain::Create);
	Net::MainServer::Instance().GetACCreater()->Registe(Common::NETMSG_GETBUDDIES , &Net::ACGetBuddy::Create);
	Net::MainServer::Instance().GetACCreater()->Registe(Common::NETMSG_SENDGPS , &Net::ACUploadGps::Create);
	Net::MainServer::Instance().GetACCreater()->Registe(Common::NETMSG_SENDCONTACTS , &Net::ACUploadContacts::Create);
	DB::LoginDB lgdb;
	//DB::LoginDBError err=lgdb.Login("18664846854","123456");
	//if(DB::error_user_notexsit == err)
	//err=lgdb.Register("18664846854","123456");
	char c;
	while(c = getchar())
	{
		if('q'==c)
			break;
	}
	Net::LoginService::Instance().Stop();
	Net::MainServer::Instance().Stop();
	return 0;
}