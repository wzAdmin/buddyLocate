#include "LoginService.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include <stdio.h>
#include "DB/LoginDB.h"
#include "CommonType.h"
#include "BitStream.h"


using namespace Common;
namespace Net
{
	LoginService& LoginService::Instance()
	{
		static LoginService ins;
		return ins;
	}

	LoginService::LoginService()
	{
	}

	LoginService::~LoginService()
	{
	}

	void LoginService::Update( const RakNet::Packet* pack )
	{
		switch(pack->data[0])
		{
		case NETMSG_LOGIN:
			Login(pack);
			break;
		case NETMSG_REGISTE:
			Register(pack);
			break;
		default:
			break;
		}
	}

	void LoginService::Login( const RakNet::Packet* pack )
	{
		RakNet::BitStream bst(pack->data + 1, pack->bitSize - 1 ,false);
		char user[256] ;
		char pswd[256] ;
		bst.Read(user);
		bst.Read(pswd);
		DB::LoginDB lgdb;
		LoginError err = lgdb.Login(user , pswd);

		RakNet::BitStream bstsd;
		bstsd.Write((RakNet::MessageID)NETMSG_LOGIN);
		bstsd.Write((unsigned char) err);
		mServer->Send(&bstsd,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,pack->systemAddress,false);
	}

	void LoginService::Register( const RakNet::Packet* pack)
	{	
		RakNet::BitStream bst(pack->data + 1, pack->bitSize - 1 ,false);
		char user[256] ;
		char pswd[256] ;
		bst.Read(user);
		bst.Read(pswd);
		DB::LoginDB lgdb;
		LoginError err = lgdb.Register(user , pswd);	
		
		RakNet::BitStream bstsd;
		bstsd.Write((RakNet::MessageID)NETMSG_REGISTE);
		bstsd.Write((unsigned char) err);
		mServer->Send(&bstsd,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,pack->systemAddress,false);
	}

}


