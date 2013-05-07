#pragma once
#include "action.h"

namespace Net
{
	class AcMainLogin :
		public Common::Action
	{
	public:	
		static Common::Action* Create(RakNet::RakPeerInterface* Peer,
					 RakNet::Packet* pket){ return new AcMainLogin(Peer , pket);}
		AcMainLogin(RakNet::RakPeerInterface* Peer,
			 RakNet::Packet* pket) :Action(Peer , pket){}
		~AcMainLogin(void){}
	private:
		virtual void doWork();
		virtual Common::NetMessage GetMessageID() {return Common::NETMSG_LOGINMAIN;}
	};
}
