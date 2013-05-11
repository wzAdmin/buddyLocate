#include "UserDB.h"
#include "MySqlDB.h"
#include <assert.h>
#include <stdio.h>
#include "GpsDB.h"
#include "ContactDB.h"

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
		char gpsTable[64] = {0};
		char ContactTable[64] = {0};
		GpsDB::Create(user,gpsTable);
		ContactDB::Create(user,ContactTable);
		sprintf(sqlstmt,"INSERT INTO `%s` (`%s`,`%s`,`%s`,`%s`) VALUES('%s','%s','%s','%s')",
			  userTableName,columnuser ,columnpwd ,columngpsTable , columncontactTable,
			  user ,pswd ,gpsTable , ContactTable);

		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
	}

	char* UserDB::QueryGpsTableName( const char* user , char* tableName )
	{
		assert(tableName);
		char sqlstmt[256] = {0};
		sprintf(sqlstmt,"SELECT `%s` FROM `%s` WHERE `%s` = '%s'",
			columngpsTable , userTableName , columnuser , user);
		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(db);
		if(res && res->row_count)
		{
			MYSQL_ROW row = mysql_fetch_row(res);
			memcpy(tableName , row[0] ,strlen(row[0]));
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
		sprintf(sqlstmt,"SELECT `%s` FROM `%s` WHERE `%s` = '%s'",
			columncontactTable , userTableName , columnuser , user);
		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(db);
		if(res && res->row_count)
		{
			MYSQL_ROW row = mysql_fetch_row(res);
			memcpy(tableName , row[0] ,strlen(row[0]));
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
