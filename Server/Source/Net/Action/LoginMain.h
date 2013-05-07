#pragma once

#include "Action.h"

namespace Net
{
	class LoginMain : public Common::Action
	{
	public:
		static Common::Action* Create(RakNet::RakPeerInterface* Peer,
			const RakNet::Packet* pket){ return new LoginMain(Peer , pket);}
		LoginMain(RakNet::RakPeerInterface* Peer,
			const RakNet::Packet* pket) : Action(Peer,pket){}
	private:
		virtual void doWork();
		virtual Common::NetMessage GetMessageID() {return Common::NETMSG_LOGINMAIN;}
	};
}