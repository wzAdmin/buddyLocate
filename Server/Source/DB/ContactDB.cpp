#include "ContactDB.h"
#include "MySqlDB.h"

namespace DB
{
	static const char* Contactcolumn_id = "id";
	static const char* Contactcolumn_friend = "friend";
	ContactDB::ContactDB(void)
	{
	}


	ContactDB::~ContactDB(void)
	{
	}

	std::vector<RakNet::RakString> ContactDB::GetBuddy( const char* user )
	{
		std::vector<RakNet::RakString> buddies;
		char sqlstmt[256]={0};
		char tablename[256]={0};
		sprintf(sqlstmt , "SELECT * FROM `%s`",getTableName(user,tablename));
		mysql_real_query(MySqlDB::GetInstance().getMysql(),sqlstmt,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(MySqlDB::GetInstance().getMysql());
		int index = -1;
		if(!res)
			return buddies;
		for (unsigned int i =0;i < res->field_count;i++)
		{
			if(0 == strcmp(Contactcolumn_friend , res->fields[i].name))
			{
				index = i;
				break;
			}
		}
		if(-1 == index)
		{
			printf("can not find %s in table %s\n",Contactcolumn_friend,tablename);
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		while (row)
		{
			buddies.push_back(row[index]);
			row = mysql_fetch_row(res);
		}
		mysql_free_result(res);
		return buddies;
	}

	char* ContactDB::Create( const char* user , char* tableName )
	{
		char sqlstmt[256] = {0};
		sprintf(sqlstmt,"CREATE  TABLE buddy.%s (\
			`%s` INT NOT NULL AUTO_INCREMENT,\
			`%s` VARCHAR(45) NOT NULL,\
			PRIMARY KEY (id))\
			DEFAULT charset = utf8",getTableName(user,tableName),Contactcolumn_id , Contactcolumn_friend );
		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		return tableName;
	}

	void ContactDB::Insert( const char* user ,const char* friendid )
	{
		char sqlstmt[256]={0};
		char tablename[256]={0};
		getTableName(user,tablename);

		sprintf(sqlstmt , "SELECT * FROM `%s` WHERE `%s`='%s'" , tablename ,Contactcolumn_friend ,friendid);
		mysql_real_query(MySqlDB::GetInstance().getMysql() ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(MySqlDB::GetInstance().getMysql());

		if(!res || !res->row_count)
		{
			sprintf(sqlstmt ,"INSERT INTO `%s` (`%s`) VALUES('%s')",tablename,Contactcolumn_friend,friendid);
			mysql_real_query(MySqlDB::GetInstance().getMysql() ,sqlstmt ,strlen(sqlstmt));
		}
		mysql_free_result(res);
	}

	char* ContactDB::getTableName( const char* user ,char* tableName )
	{
		sprintf(tableName , "Contact_%s",user);
		return tableName;
	}

}
