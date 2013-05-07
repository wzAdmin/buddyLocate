#pragma once
#include "SignaledEvent.h"
#include "RakThread.h"

namespace RakNet
{
	struct Packet;
	class RakPeerInterface;

	class RAK_DLL_EXPORT UdpService
	{
	public:
		UdpService();
		virtual ~UdpService();
		void Start(unsigned int MaxConnectionNum , unsigned short Port = 0);
		void Stop();
		RakNet::RakPeerInterface* Peer(){return mServer;}
	protected:
		virtual void OnServiceStart(){}
		virtual void OnServiceStop(){}
		virtual void Update( RakNet::Packet* pack) = 0;
		static  RAK_THREAD_DECLARATION(ThreadFunc);
	protected:
		RakNet::RakPeerInterface* mServer;
		RakNet::SignaledEvent mQuitEvent;
		bool bRuning;
	};
}
