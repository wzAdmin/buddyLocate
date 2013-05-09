#pragma once

namespace DB
{
	class UserDB
	{
	public:
		UserDB(void);
		~UserDB(void);
	public:
		void InsertUser(const char* user , const char* pswd);
		char* QueryGpsTableName(const char* user , char* tableName);
		char* QueryContactTableName(const char* user , char* tableName);
	};
}

