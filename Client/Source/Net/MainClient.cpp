#include "MainClient.h"
#include "NatPunchthroughClient.h"
#include "Action.h"
#include "RakPeerInterface.h"

namespace Net
{
	MainClient::MainClient(void)
	{
		mNpc = new RakNet::NatPunchthroughClient;
		mAcCreater = new Common::ActionCreater;
	}

	MainClient::~MainClient(void)
	{
		delete mAcCreater;
		delete mNpc;
	}

	MainClient& MainClient::Instance()
	{
		static MainClient ins;
		return ins;
	}

	void MainClient::Update( const RakNet::Packet* pack )
	{
		switch(pack->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			Common::LoginMain lgm;
			lgm.user = mUserID;
			RakNet::BitStream bst;
			lgm.ToBitStream(bst);
			mMainServerAddress = pack->systemAddress;
			mServer->Send(&bst , MEDIUM_PRIORITY,RELIABLE_ORDERED,0,pack->systemAddress,false);
			break;
		}
		if(pack->data[0] >= Common::NETMSG_BEGIN && pack->data[0] < Common::NETMSG_END)
		{
			Common::Action* ac = mAcCreater->CreateAction(Common::NetMessage(pack->data[0]) ,
				mServer , pack);
			mWorkers.AddInput(&MainClient::UerCallBack, ac );
		}
	}

	void MainClient::OnServiceStart()
	{
		mServer->AttachPlugin(mNpc);
		mWorkers.StartThreads(MaxWorkthreads,0,NULL,NULL);
	}

	void MainClient::OnServiceStop()
	{
		mServer->DetachPlugin(mNpc);
		mWorkers.StopThreads();
	}

	int MainClient::UerCallBack( Common::Action* ac, bool *returnOutput, void* perThreadData )
	{
		ac->doWork();
		delete ac;
		*returnOutput = false;
		return 0 ;
	}

	void MainClient::ConnectServer( const RakNet::RakString& host , unsigned short port )
	{
		mServer->Connect(host.C_String() , port ,NULL , 0);
	}

}
