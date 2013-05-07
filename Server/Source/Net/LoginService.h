#pragma once
#include "SignaledEvent.h"
#include "UdpService.h"

namespace RakNet
{
	class RakPeerInterface;
}
namespace Net
{
	class LoginService : public RakNet::UdpService
	{
	public:
		static LoginService& Instance();
	private:
		LoginService();
		~LoginService();
		virtual void Update(RakNet::Packet* pack);
		void Login(const RakNet::Packet* pack);
		void Register(const RakNet::Packet* pack);
	public:
		static const unsigned int MaxConnectionNum = 100;
		static const unsigned short Port = 50508;
	};
}