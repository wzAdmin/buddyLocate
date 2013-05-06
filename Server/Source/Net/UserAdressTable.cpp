#include "UserAdressTable.h"
#include "RakPeerInterface.h"

namespace Net
{
	RakNet::SystemAddress UserAdressTable::GetUserAdress( RakNet::RakString userid )
	{
		UserIt it = mUserAdress.find(userid);
		if(mUserAdress.end() == it)
			return NULL;
		else
			return mPeer->GetSystemAddressFromIndex(it->second);
	}

	void UserAdressTable::AddUser( RakNet::RakString userid , const RakNet::SystemAddress& address )
	{
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

}
