#include "UserAdressTable.h"
#include "RakPeerInterface.h"
#include "AutoMutex.h"

namespace Net
{
	RakNet::SystemAddress UserAdressTable::GetUserAdress( RakNet::RakString userid )
	{
		Common::AutoMutex automutex(&mMutex);
		UserIt it = mUserAdress.find(userid);
		if(mUserAdress.end() == it)
			return RakNet::UNASSIGNED_SYSTEM_ADDRESS;
		else
			return mPeer->GetSystemAddressFromIndex(it->second);
	}

	void UserAdressTable::AddUser( RakNet::RakString userid , const RakNet::SystemAddress& address )
	{
		Common::AutoMutex automutex(&mMutex);
		int index = mPeer->GetIndexFromSystemAddress(address);
		if(-1 != index)
		{
			UserIt it = mUserAdress.find(userid);
			if(mUserAdress.end() == it)
				mUserAdress.insert(std::pair<RakNet::RakString , int> (userid , index));
			else
				it->second = index;
		}
	}

	RakNet::RakNetGUID UserAdressTable::GetUserNetGUID( RakNet::RakString userid )
	{
		Common::AutoMutex automutex(&mMutex);
		UserIt it = mUserAdress.find(userid);
		if(mUserAdress.end() == it)
			return RakNet::UNASSIGNED_RAKNET_GUID;
		else
			return mPeer->GetGuidFromSystemAddress(
			mPeer->GetSystemAddressFromIndex(it->second));
	}

}
