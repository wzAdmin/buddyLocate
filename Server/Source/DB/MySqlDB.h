#pragma once
#include "mysql.h"

namespace DB
{
	class MySqlDB
	{
	public:
		static MySqlDB& GetInstance();
		MYSQL* getMysql(){ return &mysql;}
	private:
		MySqlDB(void);
		~MySqlDB(void);

		MYSQL mysql;
	};
}

