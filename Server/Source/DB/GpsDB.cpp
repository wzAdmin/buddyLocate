#include "GpsDB.h"
#include "UserDB.h"
#include "MySqlDB.h"
#include "mysql.h"

namespace DB
{
	static const char* gpsTable = "gpsINfo";
	static const char* gpsColumn_id       = "id";
	static const char* gpsColumn_user     = "user" ;
	static const char* gpsColumn_utcTime  = "utcTime";
	static const char* gpsColumn_latitude = "latitude";
	static const char* gpsColumn_longitude= "longitude";
	static const char* gpsColumn_address    = "address";

	GpsDB::GpsDB()
	{
	}


	GpsDB::~GpsDB(void)
	{
	}

	bool GpsDB::QueryGpsInfo( const char* user ,Common::GpsInfo& gps)
	{
		char sqlstmt[256] = {0};
		sprintf(sqlstmt , "SELECT * FROM `%s` WHERE `%s`='%s'" ,
			gpsTable , gpsColumn_user ,user);
	
		mysql_real_query(MySqlDB::GetInstance().getMysql(), sqlstmt , strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(MySqlDB::GetInstance().getMysql());
		if(!res || !res->row_count)
		{
			mysql_free_result(res);
			return false;
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		for (unsigned int i = 0; i < res->field_count; i ++)
		{
			if(strcmp(gpsColumn_utcTime , res->fields[i].name))
			{
				gps.utcTime = _atoi64(row[i]);
			}
			else if(strcmp(gpsColumn_latitude , res->fields[i].name))
			{
				gps.Latitude = atoi(row[i]);
			}
			else if(strcmp(gpsColumn_longitude , res->fields[i].name))
			{
				gps.Longitude = atoi(row[i]);
			}
			else if(strcmp(gpsColumn_address , res->fields[i].name))
			{
				gps.Address = row[i];
			}
		}
		mysql_free_result(res);
		return true;
	}

	char* GpsDB::Create( const char* user ,char* tableName)
	{
		char sqlstmt[512] = {0};
		sprintf(sqlstmt,"CREATE  TABLE buddy.%s (\
			`%s` INT NOT NULL AUTO_INCREMENT,\
			`%s` BIGINT NOT NULL,\
			`%s` INT NOT NULL,\
			`%s` INT NOT NULL,\
			PRIMARY KEY (id))\
			DEFAULT charset = utf8",
			getTableName(user,tableName),gpsColumn_id  ,gpsColumn_utcTime,gpsColumn_latitude , gpsColumn_longitude);
		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		return tableName;
	}

	void GpsDB::Insert( const char* user ,const Common::GpsInfo& gps )
	{
		char sqlstmt[512] = {0};
		char tablename[256]={0};
		getTableName(user,tablename);

		MYSQL* db = MySqlDB::GetInstance().getMysql();
		sprintf(sqlstmt , "SELECT * FROM `%s` WHERE `%s`='%s'",gpsTable,gpsColumn_user,user);
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		MYSQL_RES* res = mysql_store_result(db);
		if(!res || !res->row_count)
		{
			sprintf(sqlstmt,"INSERT INTO `%s` (`%s`,`%s`,`%s`,`%s`,`%s`)\
					VALUES('%s','%lld','%d','%d','%s')",
				gpsTable , gpsColumn_user ,gpsColumn_utcTime ,gpsColumn_latitude , gpsColumn_longitude,gpsColumn_address,
			user,gps.utcTime ,gps.Latitude,gps.Longitude,gps.Address.C_String());
			mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		}
		else
		{
			sprintf(sqlstmt,"UPDATE `%s` SET `%s` = '%lld',`%s` = '%d',`%s` = '%d',`%s` = '%s' \
							WHERE `%s`='%s'",
							gpsTable ,gpsColumn_utcTime ,gps.utcTime,gpsColumn_latitude , gps.Latitude,
							gpsColumn_longitude,gps.Longitude,gpsColumn_address,gps.Address.C_String(),gpsColumn_user,user);
			mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		}
		mysql_free_result(res);

		sprintf(sqlstmt,"INSERT INTO `%s` (`%s`,`%s`,`%s`) VALUES('%lld','%d','%d')",
			tablename , gpsColumn_utcTime ,gpsColumn_latitude ,gpsColumn_longitude , gps.utcTime , gps.Latitude,gps.Longitude);
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));

	}

	char* GpsDB::getTableName( const char* user ,char* tableName )
	{
		sprintf(tableName , "gpsINfo_%s" , user);
		return tableName;
	}

}
