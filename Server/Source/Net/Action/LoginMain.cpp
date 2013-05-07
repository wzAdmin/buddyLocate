#include "LoginMain.h"
#include "Net/MainServer.h"
#include "Net/UserAdressTable.h"
#include "RakPeerInterface.h"

namespace Net
{
	void LoginMain::doWork()
	{
		UserAdressTable* AdTable = MainServer::Instance().GetUserAdressTable();
		Common::LoginMain lgm(mpket->data , mpket->bitSize);
		AdTable->AddUser(lgm.user,mpket->systemAddress);
		Common::RELoginMain re;
		re.result = Common::RELoginMain::Login_Success;
		RakNet::BitStream bst;
		re.ToBitStream(bst);
		mPeer->Send(&bst , MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mpket->systemAddress,false);
	}
}

