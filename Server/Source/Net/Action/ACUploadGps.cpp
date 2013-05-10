#include "ACUploadGps.h"
#include "DB/GpsDB.h"
#include "Net/MainServer.h"
#include "Net/UserAdressTable.h"

namespace Net
{
	void ACUploadGps::doWork()
	{
		Common::SendGps gps(mpket->data , mpket->bitSize);
		DB::GpsDB::Insert(MainServer::Instance().GetUserAdressTable()->GetUser(mpket->guid),gps.location);
		printf("GetGps From %s : Lat=%d Lon=%d Time = %lld\n", mpket->systemAddress.ToString(),
			gps.location.Latitude , gps.location.Longitude ,gps.location.utcTime);
	}
}
