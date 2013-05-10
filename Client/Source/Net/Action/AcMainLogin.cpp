#include "AcMainLogin.h"
#include "RakPeerInterface.h"
#include "Net/LoginCallBack.h"
#include "Net/MainClient.h"

namespace Net
{
	void AcMainLogin::doWork()
	{
		if(MainClient::Instance().mCallBack)
			MainClient::Instance().mCallBack->OnLoginReulst(LGE_none);
	}

}
