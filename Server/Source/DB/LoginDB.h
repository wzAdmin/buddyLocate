#pragma once
#include "CommonType.h"
namespace sql
{
	class Connection;
}
namespace DB
{

	class LoginDB
	{
	public:
		LoginDB(void);
		~LoginDB(void);
	public:
		Common::LoginError Login(const char* user , const char* pswd);
		Common::LoginError Register(const char* user , const char* pswd);
	private:
		sql::Connection* connect();
	};
}

