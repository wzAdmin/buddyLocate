#pragma once
#include <map>
#include "UdpService.h"
#include "ThreadPool.h"

namespace Common
{
	class ActionCreater;
	class Action;
}
namespace RakNet
{
	class NatPunchthroughServer;
}

namespace Net
{
	class UserAdressTable;

	class MainServer : 
		public RakNet::UdpService
	{
	private:
		MainServer();
		~MainServer();
	public:
		static MainServer& Instance();
		Common::ActionCreater* GetACCreater(){return mAcCreater;}
		UserAdressTable* GetUserAdressTable(){return mUserTable;}
	private:
		virtual void Update(const RakNet::Packet* pack);
		virtual void OnServiceStart();
		virtual void OnServiceStop();

		static int UerCallBack(Common::Action* ac, bool *returnOutput, void* perThreadData);

		RakNet::NatPunchthroughServer* mNps;
		Common::ActionCreater* mAcCreater;
		UserAdressTable* mUserTable;
		ThreadPool<Common::Action* , int> mWorkers;

		const static unsigned int MaxWorkthreads = 10;
	public:
		const static unsigned int MaxConnectionNum = 300;
		const static unsigned short Port = 50608;

	};
}