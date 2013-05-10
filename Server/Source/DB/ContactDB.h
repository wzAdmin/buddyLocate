#pragma once
#include <vector>
#include "RakString.h"

namespace DB
{
	class ContactDB
	{
	private:
		ContactDB(void);
		~ContactDB(void);
	public:
		static std::vector<RakNet::RakString> GetBuddy(const char* user);
		static char* Create(const char* user , char* tableName);
		static void Insert( const char* user ,const char* friendid);
		static char* getTableName(const char* user ,char* tableName);
	};
}

