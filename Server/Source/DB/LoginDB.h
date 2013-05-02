#pragma once
namespace sql
{
	class Connection;
}
namespace DB
{
	enum LoginDBError
	{
		error_none,
		error_user_notexsit,
		error_user_exsited,
		error_password_incorrect,
		error_unkown
	};
	class LoginDB
	{
	public:
		LoginDB(void);
		~LoginDB(void);
	public:
		LoginDBError Login(const char* user , const char* pswd);
		LoginDBError Register(const char* user , const char* pswd);
	private:
		sql::Connection* connect();
	};
}

