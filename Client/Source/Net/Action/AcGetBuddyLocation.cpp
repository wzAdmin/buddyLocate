#include "AcGetBuddyLocation.h"

namespace Net
{

	void Net::AcGetBuddyLocation::doWork()
	{
		Common::BuddyLocation bdl(mpket->data , mpket->bitSize);
		PlatformWork(bdl);
	}
}
