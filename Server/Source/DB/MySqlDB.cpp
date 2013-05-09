#include "MySqlDB.h"

namespace DB
{

	MySqlDB::MySqlDB(void)
	{
		mysql_init(&mysql);
		mysql_real_connect(&mysql,"127.0.0.1","root" , "root" ,"Buddy",3306 ,NULL,0);
	}


	MySqlDB::~MySqlDB(void)
	{
		mysql_shutdown(&mysql,SHUTDOWN_DEFAULT);
	}

	MySqlDB& MySqlDB::GetInstance()
	{
		static MySqlDB db;
		return db;
	}

}
