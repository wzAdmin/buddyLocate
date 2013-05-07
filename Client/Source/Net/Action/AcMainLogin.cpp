#include "AcMainLogin.h"
#include "RakPeerInterface.h"

namespace Net
{

	void AcMainLogin::doWork()
	{
		Common::GetBuddies getbd;
		RakNet::BitStream bst;
		getbd.ToBitStream(bst);
		mPeer->Send(&bst ,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mpket->systemAddress,false);
	}

}
