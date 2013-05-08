#include "ACGetBuddy.h"
#include "CommonType.h"
#include "Net/UserAdressTable.h"
#include "Net/MainServer.h"
#include "RakPeerInterface.h"

namespace Net
{
	void Net::ACGetBuddy::doWork()
	{

		// TODO there need do the actually things
		Common::REGetBuddies rebds;
		Common::Buddy bd;
		bd.userid = "18664876864";
		bd.userAddress = MainServer::Instance().GetUserAdressTable()->GetUserAdress(bd.userid);
		bd.NetGuid = MainServer::Instance().GetUserAdressTable()->GetUserNetGUID(bd.userid);
		RakNet::BitStream bst;
		rebds.Buddies.push_back(bd);
		rebds.ToBitStream(bst);
		mPeer->Send(&bst ,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mpket->systemAddress,false);
	}
}
