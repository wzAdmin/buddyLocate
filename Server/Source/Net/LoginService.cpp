#include "LoginService.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include <stdio.h>

namespace Net
{
	LoginService& LoginService::Instance()
	{
		static LoginService ins;
		return ins;
	}

	LoginService::LoginService()
	{
		bRuning = false;
		mQuitEvent.InitEvent();
	}

	LoginService::~LoginService()
	{
		Stop();
		mQuitEvent.CloseEvent();
	}

	void LoginService::Start()
	{
		mServer = RakNet::RakPeerInterface::GetInstance();
		RakNet::SocketDescriptor sdp(Port,NULL);
		sdp.socketFamily = AF_INET;
		RakNet::StartupResult res = mServer->Startup(MaxConnectionNum,&sdp,1);
		mServer->SetMaximumIncomingConnections(MaxConnectionNum);
		RakAssert(res == RakNet::RAKNET_ALREADY_STARTED || res == RakNet::RAKNET_STARTED);
		RakNet::RakThread::Create(ThreadFunc,this);
		while(!bRuning)
			RakSleep(10);
		printf("LoginService Started\n");
	}

	unsigned int __stdcall LoginService::ThreadFunc( void* param)
	{
		LoginService* LgS = (LoginService*)param;
		LgS->bRuning = true;
		RakNet::Packet* p = NULL;
		while (LgS->bRuning)
		{
			while (p = LgS->mServer->Receive())
			{
				LgS->mServer->DeallocatePacket(p);
			}
			LgS->mQuitEvent.WaitOnEvent(10);
		}
		LgS->bRuning = false;
		return NULL;
	}

	void LoginService::Stop()
	{
		if(!bRuning)
			return;
		mServer->Shutdown(100);
		bRuning= false;
		mQuitEvent.SetEvent();
		while(bRuning)
			RakSleep(10);
		RakNet::RakPeerInterface::DestroyInstance(mServer);
	}

}


