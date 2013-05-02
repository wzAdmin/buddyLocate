#include "DB/LoginDB.h"
int main()
{
	DB::LoginDB lgdb;
	DB::LoginDBError err=lgdb.Login("18664846854","123456");
	if(DB::error_user_notexsit == err)
		err=lgdb.Register("18664846854","123456");
	return 0;
}