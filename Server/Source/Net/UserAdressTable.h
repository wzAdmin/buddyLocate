#pragma once
#include <map>
#include "RakNetTypes.h"
#include "RakString.h"
#include "SimpleMutex.h"


namespace RakNet
{
	class RakPeerInterface;
	class SimpleMutex;
}

namespace Net
{
	class UserAdressTable
	{
	public:
		UserAdressTable(RakNet::RakPeerInterface* peer):mPeer(peer){}
		~UserAdressTable(){}
		RakNet::SystemAddress GetUserAdress(RakNet::RakString userid);
		RakNet::RakNetGUID GetUserNetGUID(RakNet::RakString userid);
		void AddUser(RakNet::RakString userid , const RakNet::SystemAddress& address);
	private:
		RakNet::RakPeerInterface* mPeer;
		std::map<RakNet::RakString ,int> mUserAdress;
		typedef std::map<RakNet::RakString ,int>::iterator UserIt;

		RakNet::SimpleMutex mMutex;
	};
}