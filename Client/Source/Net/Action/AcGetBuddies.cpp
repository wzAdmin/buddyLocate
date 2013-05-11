#include "AcGetBuddies.h"
#include "Net/MainClient.h"
#include "NatPunchthroughClient.h"

namespace Net
{
	void AcGetBuddies::doWork()
	{
		Common::REGetBuddies buddys(mpket->data , mpket->bitSize);
		PlatformWork(buddys);
	}

}
