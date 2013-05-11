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
		const char* GetUser(const RakNet::RakNetGUID& guid);
		void Remove(const RakNet::RakNetGUID& guid);
	private:
		RakNet::RakPeerInterface* mPeer;
		std::map<RakNet::RakString ,int> mUserAdress;
		std::map<RakNet::RakNetGUID ,RakNet::RakString> mGUIDtoUser;
		typedef std::map<RakNet::RakString ,int>::iterator UserIt;
		typedef std::map<RakNet::RakNetGUID ,RakNet::RakString>::iterator GUIDIt;

		RakNet::SimpleMutex mMutex;
	};
}