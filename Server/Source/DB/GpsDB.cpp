#include "GpsDB.h"
#include "UserDB.h"

namespace DB
{
	GpsDB::GpsDB(void)
	{
	}


	GpsDB::~GpsDB(void)
	{
	}

	Common::GpsInfo GpsDB::QueryGpsInfo( const char* user )
	{
		UserDB userdb;
		char gpsTable[64] = {0};
		char sqlstmt[256] = {0};
		//TODB not done
		return Common::GpsInfo();
	}

}
