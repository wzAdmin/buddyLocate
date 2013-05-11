#include "AcMainLogin.h"
#include "RakPeerInterface.h"
#include "Net/LoginCallBack.h"
#include "Net/MainClient.h"

namespace Net
{
	void AcMainLogin::doWork()
	{
		Common::GetBuddies gbd;
		RakNet::BitStream bst;
		gbd.ToBitStream(bst);
		MainClient::Instance().SendBitStream(&bst);
		if(MainClient::Instance().mCallBack)
			MainClient::Instance().mCallBack->OnLoginReulst(LGE_none);
	}

}
