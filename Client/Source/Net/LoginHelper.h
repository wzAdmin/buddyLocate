#pragma once

#include "UdpService.h"
#include "RakNetTypes.h"

class ILoginCallBack;

namespace Net
{
	class LoginHelper : public RakNet::UdpService
	{
		enum AfterConnect
		{
			NOTHING,
			LOGIN,
			REGISTER
		};
	public:
		LoginHelper();
		~LoginHelper(){}
		void SetCallBack(ILoginCallBack* cb){mCallBack = cb;}
		void Login(const char* user , const char* pswd);
		void Register(const char* user , const char* pswd);
	private:
		virtual void Update(const RakNet::Packet* pack);
		void ConnectServer();
		void OnLoginDone( const RakNet::Packet* pack);
		void OnRegisterDone( const RakNet::Packet* pack);

		ILoginCallBack* mCallBack;
		char mUser[256];
		char mPswd[256];
		AfterConnect mAfterConn;
		RakNet::SystemAddress mServerAdd;
		bool mConnected;
	};
}