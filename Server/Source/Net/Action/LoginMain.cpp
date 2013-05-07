#include "LoginMain.h"
#include "Net/MainServer.h"
#include "Net/UserAdressTable.h"

namespace Net
{
	void LoginMain::doWork()
	{
		UserAdressTable* AdTable = MainServer::Instance().GetUserAdressTable();
		Common::LoginMain lgm(mpket->data , mpket->bitSize);
		AdTable->AddUser(lgm.user,mpket->systemAddress);
	}
}

