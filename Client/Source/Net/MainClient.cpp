#include "MainClient.h"
#include "NatPunchthroughClient.h"
#include "Action.h"
#include "RakPeerInterface.h"
#include "Trace.h"

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

	void MainClient::Update(  RakNet::Packet* pack )
	{
		switch(pack->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION:
			LOG_Trace(LOG_INFO,"Login","New Connect %s\n" , pack->systemAddress.ToString());
			break;
		case ID_DISCONNECTION_NOTIFICATION:
		case ID_CONNECTION_LOST:
			LOG_Trace(LOG_INFO,"Login","mainConnect LOST\n");
			break;
		case ID_NAT_PUNCHTHROUGH_SUCCEEDED:
			{
				char ipaddress[256] = {0};
				pack->systemAddress.ToString(false , ipaddress);
				LOG_Trace(LOG_INFO,"Login","NAT_PUNCHTHROUGH to %s Success\n",pack->systemAddress.ToString());
				if(pack->data[1])
					mServer->Connect(ipaddress , pack->systemAddress.GetPort() , NULL , 0);
				break;
			}
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
			if(ac)
			{
				ac->doWork();
				delete ac;
			}
		}
		else
			mServer->DeallocatePacket(pack);
	}

	void MainClient::OnServiceStart()
	{
		mServer->AttachPlugin(mNpc);
	}

	void MainClient::OnServiceStop()
	{
		mServer->DetachPlugin(mNpc);
	}


	void MainClient::ConnectServer( const RakNet::RakString& host , unsigned short port )
	{
		mServer->Connect(host.C_String() , port ,NULL , 0);
	}

	void MainClient::SendBitStream(const RakNet::BitStream* bst)
	{
		mServer->Send(bst,LOW_PRIORITY,RELIABLE_ORDERED,0,mMainServerAddress,false);
	}
}
