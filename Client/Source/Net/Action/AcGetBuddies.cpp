#include "AcGetBuddies.h"
#include "Net/MainClient.h"
#include "NatPunchthroughClient.h"

namespace Net
{
	void AcGetBuddies::doWork()
	{
		Common::REGetBuddies buddys(mpket->data , mpket->bitSize);
		if(RakNet::UNASSIGNED_RAKNET_GUID != buddys.Buddies[0].NetGuid)
		{
			MainClient::Instance().GetNatClient()->OpenNAT(buddys.Buddies[0].NetGuid,
				MainClient::Instance().MainServerAddress());
		}
	}

}
