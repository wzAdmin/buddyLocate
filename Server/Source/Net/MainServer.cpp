#include "MainServer.h"
#include "NatPunchthroughServer.h"
#include "RakPeerInterface.h"
#include "Action.h"

namespace Net
{
	MainServer& MainServer::Instance()
	{
		static MainServer p2p;
		return p2p;
	}

	MainServer::MainServer()
	{
		mNps = new RakNet::NatPunchthroughServer;
		mAcCreater = new Common::ActionCreater;
	}

	MainServer::~MainServer()
	{
		delete mAcCreater;
		delete mNps;
	}

	void MainServer::OnServiceStart()
	{
		mServer->AttachPlugin(mNps);
		mWorkers.StartThreads(MaxWorkthreads , 0 , NULL ,NULL);
	}

	void MainServer::OnServiceStop()
	{
		mServer->DetachPlugin(mNps);
		mWorkers.StopThreads();
	}

	void MainServer::Update( const RakNet::Packet* pack )
	{
		if(pack->data[0] >= Common::NETMSG_BEGIN && pack->data[0] < Common::NETMSG_END)
		{
			Common::Action* ac = mAcCreater->CreateAction(Common::NetMessage(pack->data[0]));
			mWorkers.AddInput(&MainServer::UerCallBack, ac );
		}
	}

	int MainServer::UerCallBack( Common::Action* ac, bool *returnOutput, void* perThreadData )
	{
		ac->doWork();
		delete ac;
		returnOutput = false;
		return 0;
	}

}
