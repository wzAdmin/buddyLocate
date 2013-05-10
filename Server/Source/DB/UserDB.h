#pragma once

namespace DB
{
	class UserDB
	{
	private:
		UserDB(void);
		~UserDB(void);
	public:
		static void InsertUser(const char* user , const char* pswd);
		static char* QueryGpsTableName(const char* user , char* tableName);
		static char* QueryContactTableName(const char* user , char* tableName);
	};
}

