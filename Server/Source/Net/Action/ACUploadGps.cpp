#include "ACUploadGps.h"

namespace Net
{
	void ACUploadGps::doWork()
	{
		Common::SendGps gps(mpket->data , mpket->bitSize);
		printf("GetGps From %s : Lat=%d Lon=%d Time = %d\n", mpket->systemAddress.ToString(),
			gps.location.Latitude , gps.location.Longitude ,gps.location.utcTime);
	}
}
