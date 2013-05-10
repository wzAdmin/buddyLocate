#include "GpsDB.h"
#include "UserDB.h"
#include "MySqlDB.h"
#include "mysql.h"

namespace DB
{
	static const char* gpsColumn_id       = "id";
	static const char* gpsColumn_user     = "user" ;
	static const char* gpsColumn_utcTime  = "utcTime";
	static const char* gpsColumn_latitude = "latitude";
	static const char* gpsColumn_longitude= "longitude";
	static const char* gpsColumn_accuracy = "accuracy";
	static const char* gpsColumn_altitude = "altitude";
	static const char* gpsColumn_speed    = "speed";

	GpsDB::GpsDB()
	{
	}


	GpsDB::~GpsDB(void)
	{
	}

	bool GpsDB::QueryGpsInfo( const char* user ,Common::GpsInfo& gps)
	{
		char gpsTable[64] = {0};
		char sqlstmt[256] = {0};
		char* tablename = UserDB::QueryGpsTableName(user , gpsTable);
		sprintf(sqlstmt , "SELECT TOP 1 * FROM `%s` ORDER BY `%s` DESC" ,
			gpsTable , gpsColumn_id);
	
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
			else if(strcmp(gpsColumn_latitude , res->fields[i].name))
			{
				gps.Altitude = atoi(row[i]);
			}
			else if(strcmp(gpsColumn_accuracy , res->fields[i].name))
			{
				gps.Accuracy = atoi(row[i]);
			}	
			else if(strcmp(gpsColumn_speed , res->fields[i].name))
			{
				gps.Speed = atoi(row[i]);
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
			`%s` VARCHAR(45) NOT NULL,\
			`%s` BIGINT NOT NULL,\
			`%s` INT NOT NULL,\
			`%s` INT NOT NULL,\
			`%s` INT NOT NULL,\
			`%s` INT NOT NULL,\
			`%s` INT NOT NULL,\
			PRIMARY KEY (id))\
			DEFAULT charset = utf8",getTableName(user,tableName),gpsColumn_id , gpsColumn_user ,gpsColumn_utcTime,
			gpsColumn_latitude , gpsColumn_longitude , gpsColumn_accuracy ,gpsColumn_altitude , gpsColumn_speed);
		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
		return tableName;
	}

	void GpsDB::Insert( const char* user ,const Common::GpsInfo& gps )
	{
		char sqlstmt[512] = {0};
		char tablename[256]={0};
		getTableName(user,tablename);
		sprintf(sqlstmt,"INSERT INTO `%s` (`%s`,`%s`,`%s`,`%s`,`%s`,`%s`,`%s`) \
			VALUES('%s','%lld','%d','%d','%d','%d','%d')",
			tablename , gpsColumn_user ,gpsColumn_utcTime ,gpsColumn_latitude , gpsColumn_longitude,
			gpsColumn_accuracy , gpsColumn_altitude ,gpsColumn_speed,
			user,gps.utcTime ,gps.Latitude,gps.Longitude,gps.Accuracy,gps.Altitude,gps.Speed);

		MYSQL* db = MySqlDB::GetInstance().getMysql();
		mysql_real_query(db ,sqlstmt ,strlen(sqlstmt));
	}

	char* GpsDB::getTableName( const char* user ,char* tableName )
	{
		sprintf(tableName , "gpsINfo_%s" , user);
		return tableName;
	}

}
