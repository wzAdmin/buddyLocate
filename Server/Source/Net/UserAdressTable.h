#pragma once
#include <map>
#include "RakNetTypes.h"
#include "RakString.h"

namespace RakNet
{
	class RakPeerInterface;
}

namespace Net
{
	class UserAdressTable
	{
	public:
		UserAdressTable(RakNet::RakPeerInterface* peer):mPeer(peer){}
		~UserAdressTable(){}
		RakNet::SystemAddress GetUserAdress(RakNet::RakString userid);
		void AddUser(RakNet::RakString userid , const RakNet::SystemAddress& address);
	private:
		RakNet::RakPeerInterface* mPeer;
		std::map<RakNet::RakString ,int> mUserAdress;
		typedef std::map<RakNet::RakString ,int>::iterator UserIt;
	};
}