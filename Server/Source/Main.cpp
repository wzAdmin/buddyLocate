#include "DB/LoginDB.h"
#include <stdlib.h>
int main()
{
	DB::LoginDB lgdb;
	DB::LoginDBError err=lgdb.Login("18664846854","123456");
	if(DB::error_user_notexsit == err)
		err=lgdb.Register("18664846854","123456");
	system("pause");
	return 0;
}