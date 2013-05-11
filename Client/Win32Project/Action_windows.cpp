#ifdef WIN32
#include "Net/Action/AcGetBuddies.h"
#include "Net/Action/AcGetBuddyLocation.h"
#include "Net/MainClient.h"

namespace Net
{
	void AcGetBuddies::PlatformWork(const Common::REGetBuddies& buddys)
	{
		Common::SendGps sendData;
		sendData.location.Accuracy = 1;
		sendData.location.Altitude = 2;
		sendData.location.Latitude = 1999;
		sendData.location.Longitude = 1999;
		sendData.location.Speed = 111;
		sendData.location.utcTime = 10000000;
		RakNet::BitStream bst;
		sendData.ToBitStream(bst);
		Net::MainClient::Instance().SendBitStream(&bst);
	}
	void AcGetBuddyLocation::PlatformWork(const Common::BuddyLocation& bdl)
	{

	}
}
#endif