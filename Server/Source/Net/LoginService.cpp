#include "LoginService.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include <stdio.h>
#include "DB/LoginDB.h"
#include "CommonType.h"
#include "BitStream.h"
#include "MainServer.h"

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

	void LoginService::Update( RakNet::Packet* pack )
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
		mServer->DeallocatePacket(pack);
	}

	void LoginService::Login( const RakNet::Packet* pack )
	{
		printf("IP:%s want to Login\n",pack->systemAddress.ToString());
		Common::Login bst(pack->data , pack->bitSize);
		DB::LoginDB lgdb;
		LoginError err = lgdb.Login(bst.user.C_String() , bst.pswd.C_String());
		Common::RELogin relogin;
		relogin.result = (unsigned char)err;
		RakNet::BitStream bstsd;
		if(LGE_none == err)
		{
			relogin.MainServer = "192.168.1.145";
			relogin.port = MainServer::Port;
		}
		relogin.ToBitStream(bstsd);
		mServer->Send(&bstsd,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,pack->systemAddress,false);
	}

	void LoginService::Register( const RakNet::Packet* pack)
	{	
		printf("IP:%s want to Register\n",pack->systemAddress.ToString());
		Common::Regsite bst(pack->data, pack->bitSize);
		DB::LoginDB lgdb;
		LoginError err = lgdb.Register(bst.user.C_String() , bst.pswd.C_String());	
		
		Common::RERegsite re;
		re.result = err;
		RakNet::BitStream bstsd;
		if(LGE_none == err)
		{
			re.MainServer = "192.168.1.145";
			re.port = MainServer::Port;
		}
		re.ToBitStream(bstsd);
		mServer->Send(&bstsd,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,pack->systemAddress,false);
	}

}


