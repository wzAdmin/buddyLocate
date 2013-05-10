#include "UserDB.h"
#include "MySqlDB.h"
#include <assert.h>
#include <stdio.h>

namespace DB
{
	static const char* userTableName = "user";

	static const char* columnuser = "user";

	static const char* columnpwd =	"pwd";

	static const char* columngpsTable = "gpsTable";

	static const char* columncontactTable = "contactTable";

	UserDB::UserDB(void)
	{
	}


	UserDB::~UserDB(void)
	{
	}

	void UserDB::InsertUser( const char* user , const char* pswd )
	{
		char sqlstmt[512] = {0};
		sprintf(sqlstmt,"INSERT INTO `%s` (`%s`,`%s`,`%s`,`%s`) VALUES(`%s`,`%s`,`%s_%s`,`%s_%s`)",
			userTableName , columnuser ,columnpwd ,columngpsTable , columngpsTable,
			user,pswd,user,columngpsTable ,user , columngpsTable);

		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
	}

	char* UserDB::QueryGpsTableName( const char* user , char* tableName )
	{
		assert(tableName);
		char sqlstmt[256] = {0};
		sprintf(sqlstmt,"SELECT `%s` FROM `%s` WHERE `%s` = `%s`",
			columngpsTable , userTableName , columnuser , user);
		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(db);
		if(res->row_count)
		{
			memcpy(tableName , res->row[0] ,strlen(res->row[0]));
			mysql_free_result(res);
			return tableName;
		}
		else
		{
			mysql_free_result(res);
			return NULL;
		}
	}

	char* UserDB::QueryContactTableName( const char* user , char* tableName )
	{
		assert(tableName);
		char sqlstmt[256] = {0};
		sprintf(sqlstmt,"SELECT `%s` FROM `%s` WHERE `%s` = `%s`",
			columncontactTable , userTableName , columnuser , user);
		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(db);
		if(res->row_count)
		{
			memcpy(tableName , res->row[0] ,strlen(res->row[0]));
			mysql_free_result(res);
			return tableName;
		}
		else
		{
			mysql_free_result(res);
			return NULL;
		}
	}

}
