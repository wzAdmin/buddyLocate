#include "LoginHelper.h"
#include "RakPeerInterface.h"
#include "CommonType.h"
#include "BitStream.h"
#include "LoginCallBack.h"
#include <stdio.h>


using namespace Common;


void LoginHelper::Login( const char* user , const char* pswd )
{
	if(!mConnected)
	{
		mAfterConn = LOGIN;
		int lenuser = strlen(user);
		int lenpswd = strlen(pswd);
		memcpy(mUser , user , lenuser);
		memcpy(mPswd , pswd , lenpswd);
		mUser[lenuser] = 0;
		mPswd[lenpswd] = 0;
		ConnectServer();
	}
	else
	{
		RakNet::BitStream bst;
		bst.Write((RakNet::MessageID)NETMSG_LOGIN);
		bst.Write(mUser);
		bst.Write(mPswd);
		mServer->Send(&bst,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mServerAdd,false);
	}
}

void LoginHelper::Register( const char* user , const char* pswd )
{
	if(!mConnected)
	{
		mAfterConn = REGISTER;
		int lenuser = strlen(user);
		int lenpswd = strlen(pswd);
		memcpy(mUser , user , lenuser);
		memcpy(mPswd , pswd , lenpswd);
		mUser[lenuser] = 0;
		mPswd[lenpswd] = 0;
		ConnectServer();
	}
	else
	{
		RakNet::BitStream bst;
		bst.Write((RakNet::MessageID)NETMSG_REGISTE);
		bst.Write(mUser);
		bst.Write(mPswd);
		mServer->Send(&bst,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mServerAdd,false);
	}
}

void LoginHelper::Update( const RakNet::Packet* pack )
{
	switch(pack->data[0])
	{
	case ID_CONNECTION_REQUEST_ACCEPTED:
		mServerAdd = pack->systemAddress;
		mConnected = true;
		if(LOGIN == mAfterConn)
			Login(mUser,mPswd);
		else if(REGISTER == mAfterConn)
			Register(mUser,mPswd);
		mAfterConn = NOTHING;
		printf("Connect Success\n");
		break;
	case NETMSG_LOGIN:
		OnLoginDone(pack);
		break;
	case NETMSG_REGISTE:
		OnRegisterDone(pack);
		break;
	}
}

LoginHelper::LoginHelper():mConnected(false),mAfterConn(NOTHING),mCallBack(NULL)
{

}

void LoginHelper::ConnectServer()
{
	mServer->Connect("localhost",50508,NULL,0);
}

void LoginHelper::OnLoginDone(  const RakNet::Packet* pack )
{
	RakNet::BitStream bst(pack->data + 1,pack->bitSize - 1,false);
	unsigned char err;
	bst.Read(err);
	if(LGE_none == err)
		printf("Login Success\n");
	else if(LGE_password_incorrect == err)
		printf("Pass Word Incorrect\n");
	else if(LGE_user_notexist)
	{
		printf("User  not Existed\n");
		Register(mUser , mPswd);
	}
	if(mCallBack)
		mCallBack->OnLoginReulst(LoginError(err));
}

void LoginHelper::OnRegisterDone(  const RakNet::Packet* pack )
{
	RakNet::BitStream bst(pack->data + 1,pack->bitSize - 1,false);
	unsigned char err;
	bst.Read(err);
	if(LGE_none == err)
		printf("Register Success\n");
	else if(LGE_user_existed)
	{
		printf("User Existed\n");
	}
	if(mCallBack)
		mCallBack->OnRegisterResult(LoginError(err));
}

