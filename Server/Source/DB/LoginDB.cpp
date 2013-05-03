#include "LoginDB.h"
#include "mysql_driver.h"
#include "cppconn/statement.h"
#include "cppconn/exception.h"
#include "Platform/platform.h"

using namespace Common;
namespace DB
{
	LoginDB::LoginDB(void)
	{
	}


	LoginDB::~LoginDB(void)
	{
	}

	Common::LoginError LoginDB::Login( const char* user , const char* pswd )
	{
		Common::LoginError er = LGE_none;
		sql::ResultSet* reshead = NULL;
		sql::Connection* conn = NULL;
		sql::Statement* stmt = NULL;
		try
		{
			conn = connect();
			stmt = conn->createStatement();
			char sqlstmt[256] = {0};
			sprintf(sqlstmt,"SELECT * FROM Login WHERE user = %s",user);
			sql::ResultSet* res = stmt->executeQuery(sqlstmt);
			reshead = res;
			if(res->next())
			{
				if(res->getString("pswd") == sql::SQLString(pswd,strlen(pswd)))
					er =  LGE_none;
				else
					er = LGE_password_incorrect;
			}
			else
				er = LGE_user_notexsit;
		}

		catch(const sql::SQLException& e)
		{
			printf("%s",e.getSQLState().c_str());
			er = LGE_unkown;
		}
		delete reshead;
		delete stmt;
		delete conn;
		return er;
	}

	Common::LoginError LoginDB::Register( const char* user , const char* pswd )
	{
		LoginError re = LGE_none;
		sql::ResultSet* reshead = NULL;
		sql::Connection* conn = NULL;
		sql::Statement* stmt = NULL;

		try
		{
			conn = connect();
			stmt = conn->createStatement();

			char sqlstmt[256] = {0};
			sprintf(sqlstmt,"SELECT * FROM Login WHERE `user` = '%s'",user);
			sql::ResultSet* res = stmt->executeQuery(sqlstmt);
			if(res->next())
			{
				re = LGE_user_exsited;
			}
			else
			{
				sprintf(sqlstmt,"INSERT INTO Login (`user`,`pswd`,`time`) VALUES('%s','%s','%s')",user,pswd,GetTime().c_str());
				if(!stmt->execute(sqlstmt))
					re = LGE_none;
				else
					re = LGE_unkown;
			}
		}
		catch(const sql::SQLException& e)
		{
			printf("%s",e.getSQLState().c_str());
			re = LGE_unkown;
		}
		delete reshead;
		delete stmt;
		delete conn;
		return re;
	}

	sql::Connection* LoginDB::connect()
	{
		sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
		sql::Connection* conn  = driver->connect("localhost:3307","root","root");
		conn->setSchema("Buddy");
		return conn;
	}

}
