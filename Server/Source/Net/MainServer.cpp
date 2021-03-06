#include "MainServer.h"
#include "NatPunchthroughServer.h"
#include "RakPeerInterface.h"
#include "Action.h"
#include "UserAdressTable.h"

namespace Net
{
	MainServer& MainServer::Instance()
	{
		static MainServer p2p;
		return p2p;
	}

	MainServer::MainServer():mUserTable(NULL)
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
		mUserTable = new UserAdressTable(mServer);
	}

	void MainServer::OnServiceStop()
	{
		mServer->DetachPlugin(mNps);
		mWorkers.StopThreads();
		delete mUserTable;
		mUserTable = NULL;
	}

	void MainServer::Update( RakNet::Packet* pack )
	{
		switch(pack->data[0])
		{
		case ID_DISCONNECTION_NOTIFICATION:
		case ID_CONNECTION_LOST:
			printf("%s Logout\n",pack->systemAddress.ToString());
			mUserTable->Remove(pack->guid);
			break;
		}
		if(pack->data[0] >= Common::NETMSG_BEGIN && pack->data[0] < Common::NETMSG_END)
		{
			Common::Action* ac = mAcCreater->CreateAction(Common::NetMessage(pack->data[0]) ,
				mServer , pack);
			if(ac)
				mWorkers.AddInput(&MainServer::UerCallBack, ac );
		}
		else
		{
			mServer->DeallocatePacket(pack);
		}
	}

	int MainServer::UerCallBack( Common::Action* ac, bool *returnOutput, void* perThreadData )
	{
		ac->doWork();
		delete ac;
		*returnOutput = false;
		return 0;
	}
}
