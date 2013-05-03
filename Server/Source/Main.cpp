#include "DB/LoginDB.h"
#include "Net/LoginService.h"
#include <stdio.h>

int main()
{
	Net::LoginService::Instance().Start(Net::LoginService::MaxConnectionNum , Net::LoginService::Port);
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
	return 0;
}