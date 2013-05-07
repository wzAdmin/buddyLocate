#pragma once
#include "BitStream.h"

namespace Common
{
	typedef struct _GpsInfo 
	{
		/************************************************************************/
		/*the UTC time, in milliseconds since January 1, 1970                    */
		/************************************************************************/
		unsigned long long utcTime;

		/************************************************************************/
		/* Latitude and Longitude are double value * 1000000  */
		/************************************************************************/
		int Latitude;
		int Longitude;

		/************************************************************************/
		/*       Accuracy in m        Altitude in m       Speed in m/s           */
		/************************************************************************/
		int  Accuracy;
		int  Altitude;
		int  Speed;
	}GpsInfo;
}
namespace RakNet
{
	template<>
	inline void RakNet::BitStream::Write(const Common::GpsInfo& gps)
	{
		Write(gps.utcTime);
		Write(gps.Longitude);
		Write(gps.Latitude);
		Write(gps.Accuracy);
		Write(gps.Altitude);
		Write(gps.Speed);
	}

	template<>
	inline bool RakNet::BitStream::Read(Common::GpsInfo& gps)
	{
		return Read(gps.utcTime)&&\
			Read(gps.Longitude)&&\
			Read(gps.Latitude)&&\
			Read(gps.Accuracy)&&\
			Read(gps.Altitude)&&\
			Read(gps.Speed);
	}
}
