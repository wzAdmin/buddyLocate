#pragma once

#include "UdpService.h"
#include "RakNetTypes.h"

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
	void Login(const char* user , const char* pswd);
	void Register(const char* user , const char* pswd);
private:
	virtual void Update(const RakNet::Packet* pack);
	void ConnectServer();
	void OnLoginDone( const RakNet::Packet* pack);
	void OnRegisterDone( const RakNet::Packet* pack);
	char mUser[256];
	char mPswd[256];
	AfterConnect mAfterConn;
	RakNet::SystemAddress mServerAdd;
	bool mConnected;
};