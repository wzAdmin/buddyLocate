#include "UdpService.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include <stdio.h>

namespace RakNet
{
	UdpService::UdpService()
	{
		bRuning = false;
		mQuitEvent.InitEvent();
	}

	UdpService::~UdpService()
	{
		Stop();
		mQuitEvent.CloseEvent();
	}

	void UdpService::Start(unsigned int MaxConnectionNum , unsigned short Port /*= 0*/)
	{
		mServer = RakNet::RakPeerInterface::GetInstance();
		RakNet::SocketDescriptor sdp(Port,NULL);
		sdp.socketFamily = AF_INET;
		RakNet::StartupResult res = mServer->Startup(MaxConnectionNum,&sdp,1);
		mServer->SetMaximumIncomingConnections(MaxConnectionNum);
		mServer->SetOccasionalPing(true);
		RakAssert(res == RakNet::RAKNET_ALREADY_STARTED || res == RakNet::RAKNET_STARTED);
		RakNet::RakThread::Create(ThreadFunc,this);
		while(!bRuning)
			RakSleep(10);
		printf("prot::%d Started\n",Port);
	}

	RAK_THREAD_DECLARATION(UdpService::ThreadFunc)
	{
		UdpService* LgS = (UdpService*)arguments;
		LgS->bRuning = true;
		RakNet::Packet* p = NULL;
		LgS->OnServiceStart();
		while (LgS->bRuning)
		{
			while (p = LgS->mServer->Receive())
			{
				LgS->Update(p);
				LgS->mServer->DeallocatePacket(p);
			}
			LgS->mQuitEvent.WaitOnEvent(10);
		}
		LgS->bRuning = false;
		LgS->OnServiceStop();
		return NULL;
	}

	void UdpService::Stop()
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


