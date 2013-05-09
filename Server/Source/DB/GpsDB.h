#pragma once
#include "CommonType.h"

namespace DB
{
	class GpsDB
	{
	public:
		GpsDB(void);
		~GpsDB(void);
	public:
		Common::GpsInfo QueryGpsInfo(const char* user);
	};
}

