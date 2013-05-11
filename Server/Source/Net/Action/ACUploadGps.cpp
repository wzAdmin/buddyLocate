#include "ACUploadGps.h"
#include "DB/GpsDB.h"
#include "DB/ContactDB.h"
#include "Net/MainServer.h"
#include "Net/UserAdressTable.h"
#include "RakPeerInterface.h"


namespace Net
{
	void ACUploadGps::doWork()
	{
		Common::SendGps gps(mpket->data , mpket->bitSize);
		const char* user = MainServer::Instance().GetUserAdressTable()->GetUser(mpket->guid);
		DB::GpsDB::Insert(user,gps.location);

		//通知好友自己的位置
		Common::BuddyLocation bdl ;
		bdl.userid = user;
		bdl.gps = gps.location;
		RakNet::BitStream bst;
		bdl.ToBitStream(bst);
		std::vector<RakNet::RakString> contacts = DB::ContactDB::GetBuddy(user);
		for(unsigned int i = 0; i < contacts.size() ;i ++)
		{
			RakNet::SystemAddress add = MainServer::Instance().GetUserAdressTable()->GetUserAdress(contacts[i]);
			//好友在线
			if(UNASSIGNED_SYSTEM_ADDRESS != add)
			{
				mPeer->Send(&bst ,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,add,false);
			}
		}

		printf("GetGps From %s : Lat=%d Lon=%d Time = %lld\n", mpket->systemAddress.ToString(),
			gps.location.Latitude , gps.location.Longitude ,gps.location.utcTime);
	}
}
