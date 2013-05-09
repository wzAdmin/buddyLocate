#include "LoginDB.h"
#include "Platform/platform.h"
#include "MySqlDB.h"

using namespace Common;
namespace DB
{
	LoginDB::LoginDB(void)
	{
	}


	LoginDB::~LoginDB(void)
	{
	}

	Common::LoginError LoginDB::Login( const char* user , const char* pswd )
	{
		Common::LoginError er = LGE_none;
		char sqlstmt[256] = {0};
		sprintf(sqlstmt,"SELECT * FROM Login WHERE `user` = '%s'",user);

		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(db);
		if(res->row_count)
		{
			MYSQL_ROW row = mysql_fetch_row(res);
			std::string str(pswd);
			const static std::string StrPswd("pswd");
			int index = -1;
 			for ( unsigned int i = 0; i < res->field_count ; i++)
 			{
				if(StrPswd == res->fields[i].name)
					index = i;
 			}
			if(-1 == index)
				er = LGE_unkown;
			else if(str == row[index])
				er = LGE_none;
			else
				er = LGE_password_incorrect;
		}
		else
		{
			er = LGE_user_notexist;
		}
		mysql_free_result(res);
		return er;
	}

	Common::LoginError LoginDB::Register( const char* user , const char* pswd )
	{
		LoginError re = LGE_none;
		char sqlstmt[256] = {0};
		sprintf(sqlstmt,"SELECT * FROM Login WHERE `user` = '%s'",user);

		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(db);
		if(res->row_count)
			re = LGE_user_existed;
		else
		{
			sprintf(sqlstmt,"INSERT INTO Login (`user`,`pswd`,`time`) VALUES('%s','%s','%s')",user,pswd,GetTime().c_str());
			mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
			re = LGE_none;
		}
		return re;
	}
}
