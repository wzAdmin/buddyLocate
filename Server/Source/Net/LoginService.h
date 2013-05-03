#pragma once
#include "SignaledEvent.h"

namespace RakNet
{
	class RakPeerInterface;
}
namespace Net
{
	class LoginService
	{
	public:
		static LoginService& Instance();
		void Start();
		void Stop();
	private:
		LoginService();
		~LoginService();
		void Update();
		static unsigned int __stdcall ThreadFunc(void* param);
	private:
		static const unsigned int MaxConnectionNum = 100;
		static const unsigned int Port = 50508;
		RakNet::RakPeerInterface* mServer;
		RakNet::SignaledEvent mQuitEvent;
		bool bRuning;
	};
}