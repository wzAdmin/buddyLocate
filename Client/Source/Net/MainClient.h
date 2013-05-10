#pragma once
#include "udpservice.h"
#include "ThreadPool.h"
#include "RakString.h"

namespace Common
{
	class ActionCreater;
	class Action;
}
namespace RakNet
{
	class NatPunchthroughClient;
	class BitStream;
}

namespace Net
{
	class ILoginCallBack;
	class MainClient :
		public RakNet::UdpService
	{
	public:
		MainClient(void);
		~MainClient(void);
		static MainClient& Instance();
		RakNet::NatPunchthroughClient* GetNatClient(){return mNpc;}
		Common::ActionCreater* GetACCreater(){return mAcCreater;}
		void ConnectServer(const RakNet::RakString& host , unsigned short port);
		const RakNet::RakString& UserID() const { return mUserID; }
		void UserID(const RakNet::RakString& val) { mUserID = val; }
		RakNet::SystemAddress MainServerAddress() const { return mMainServerAddress; }
		void SendBitStream(const RakNet::BitStream* bst);
	public:
		ILoginCallBack* mCallBack;
		const static unsigned int MaxConnectionNum = 30;
	private:
		virtual void Update( RakNet::Packet* pack);
		virtual void OnServiceStart();
		virtual void OnServiceStop();
#ifdef ANDROID
		void AttachThread();
		void DetachThread();
#endif
		RakNet::RakString mUserID;
		RakNet::SystemAddress mMainServerAddress;
		RakNet::NatPunchthroughClient* mNpc;
		Common::ActionCreater* mAcCreater;

		const static unsigned int MaxWorkthreads = 10;
	};
}
