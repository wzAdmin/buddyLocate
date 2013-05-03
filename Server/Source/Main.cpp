#include "DB/LoginDB.h"
#include "Net/LoginService.h"
#include <stdlib.h>
int main()
{
	Net::LoginService::Instance().Start();
	DB::LoginDB lgdb;
	//DB::LoginDBError err=lgdb.Login("18664846854","123456");
	//if(DB::error_user_notexsit == err)
		//err=lgdb.Register("18664846854","123456");
	system("pause");
	Net::LoginService::Instance().Stop();
	return 0;
}