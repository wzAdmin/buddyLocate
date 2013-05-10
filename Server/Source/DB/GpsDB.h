#pragma once
#include "CommonType.h"

namespace DB
{
	class GpsDB
	{
	private:
		GpsDB();
		~GpsDB(void);
	public:
		static char* Create(const char* user , char* tableName);
		static bool QueryGpsInfo(const char* user ,Common::GpsInfo& gps);
		static void Insert( const char* user ,const Common::GpsInfo& gps);
		static char* getTableName(const char* user ,char* tableName);
	};
}

