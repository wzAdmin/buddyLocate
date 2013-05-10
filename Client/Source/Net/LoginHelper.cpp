#include "LoginHelper.h"
#include "RakPeerInterface.h"
#include "CommonType.h"
#include "BitStream.h"
#include "LoginCallBack.h"
#include "Trace.h"

using namespace Common;

namespace Net
{
	void LoginHelper::Login( const char* user , const char* pswd )
	{
		int lenuser = strlen(user);
		int lenpswd = strlen(pswd);
		memcpy(mUser , user , lenuser);
		memcpy(mPswd , pswd , lenpswd);
		mUser[lenuser] = 0;
		mPswd[lenpswd] = 0;

		if(!mConnected)
		{
			mAfterConn = LOGIN;
			ConnectServer();
		}
		else
		{
			RakNet::BitStream bst;
			Common::Login lg;
			lg.pswd = pswd;
			lg.user = user;
			lg.ToBitStream(bst);
			mServer->Send(&bst,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mServerAdd,false);
		}
	}

	void LoginHelper::Register( const char* user , const char* pswd )
	{

		int lenuser = strlen(user);
		int lenpswd = strlen(pswd);
		memcpy(mUser , user , lenuser);
		memcpy(mPswd , pswd , lenpswd);
		mUser[lenuser] = 0;
		mPswd[lenpswd] = 0;

		if(!mConnected)
		{
			mAfterConn = REGISTER;
			ConnectServer();
		}
		else
		{
			RakNet::BitStream bst;
			Common::Regsite lg;
			lg.pswd = pswd;
			lg.user = user;
			lg.ToBitStream(bst);

			mServer->Send(&bst,MEDIUM_PRIORITY,RELIABLE_ORDERED,0,mServerAdd,false);
		}
	}

	void LoginHelper::Update( RakNet::Packet* pack )
	{
		switch(pack->data[0])
		{
		case ID_CONNECTION_ATTEMPT_FAILED:
			LOG_Trace(LOG_INFO,"Login","can not connect to server\n");
			MainClient::Instance().mCallBack->OnLoginReulst(LGE_cannotconnect);
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			mServerAdd = pack->systemAddress;
			mConnected = true;
			if(LOGIN == mAfterConn)
				Login(mUser,mPswd);
			else if(REGISTER == mAfterConn)
				Register(mUser,mPswd);
			mAfterConn = NOTHING;
			LOG_Trace(LOG_INFO,"Login","Connect Success\n");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
		case ID_CONNECTION_LOST:
			LOG_Trace(LOG_INFO,"Login","Connect LOST\n");
			mConnected = false;
			break;
		case NETMSG_LOGIN:
			OnLoginDone(pack);
			break;
		case NETMSG_REGISTE:
			OnRegisterDone(pack);
			break;
		}
		mServer->DeallocatePacket(pack);
	}

	LoginHelper::LoginHelper():mConnected(false),mAfterConn(NOTHING)
	{

	}

	void LoginHelper::ConnectServer()
	{
		mServer->Connect("192.168.100.100",50508,NULL,0);
	}

	void LoginHelper::OnLoginDone(  const RakNet::Packet* pack )
	{
		Common::RELogin bst(pack->data ,pack->bitSize);
		unsigned char err = bst.result;
		if(LGE_none == err)
		{
			MainClient::Instance().Start(MainClient::MaxConnectionNum );
			MainClient::Instance().UserID(mUser);
			MainClient::Instance().ConnectServer(bst.MainServer , bst.port);
			LOG_Trace(LOG_INFO,"Login","Login Success\n");
			bRuning = false;
			mConnected = false;
			return ;
		}
		else if(LGE_password_incorrect == err)
			LOG_Trace(LOG_INFO,"Login","Pass Word Incorrect\n");
		else if(LGE_user_notexist)
		{
			LOG_Trace(LOG_INFO,"Login","User  not Existed\n");
		}
		if(MainClient::Instance().mCallBack)
			MainClient::Instance().mCallBack->OnLoginReulst(LoginError(err));
	}

	void LoginHelper::OnRegisterDone(  const RakNet::Packet* pack )
	{
		Common::RERegsite bst(pack->data ,pack->bitSize);
		unsigned char err = bst.result;
		if(LGE_none == err)
		{
			MainClient::Instance().Start(MainClient::MaxConnectionNum );
			MainClient::Instance().UserID(mUser);
			MainClient::Instance().ConnectServer(bst.MainServer , bst.port);
			LOG_Trace(LOG_INFO,"Login","Register Success\n");
			bRuning = false;
			mConnected = false;
		}
		else if(LGE_user_existed == err)
		{
			LOG_Trace(LOG_INFO,"Login","User Existed\n");
		}
		else if(LGE_unkown == err)
		{
			LOG_Trace(LOG_INFO,"Login","unkown error\n");
		}
		if(MainClient::Instance().mCallBack)
			MainClient::Instance().mCallBack->OnRegisterResult(LoginError(err));
	}
}

