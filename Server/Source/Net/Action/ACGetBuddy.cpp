#include "ACGetBuddy.h"
#include "CommonType.h"
#include "Net/UserAdressTable.h"
#include "Net/MainServer.h"
#include "DB/ContactDB.h"
#include "DB/GpsDB.h"
#include "RakPeerInterface.h"

namespace Net
{
	void Net::ACGetBuddy::doWork()
	{
		Common::REGetBuddies rebds;
		Common::Buddy bd;
		const char* Clientuser = MainServer::Instance().GetUserAdressTable()->GetUser(mpket->guid);
		std::vector<RakNet::RakString> buddies = DB::ContactDB::GetBuddy(Clientuser);
		for (unsigned int i =0 ;i  < buddies.size() ; i ++)
		{
			bd.userid = buddies[i];
			if(!DB::GpsDB::QueryGpsInfo(Clientuser,bd.gps))
				bd.gps.utcTime = -1;
			bd.userAddress = MainServer::Instance().GetUserAdressTable()->GetUserAdress(bd.userid);
			bd.NetGuid = MainServer::Instance().GetUserAdressTable()->GetUserNetGUID(bd.userid);
			rebds.Buddies.push_back(bd);
		}
		RakNet::BitStream bst;
		rebds.ToBitStream(bst);
		mPeer->Send(&bst ,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mpket->systemAddress,false);
	}
}
