#pragma once
#include "action.h"

namespace Net
{

	class AcGetBuddies :
		public Common::Action
	{
	public:
		static Common::Action* Create(RakNet::RakPeerInterface* Peer,
			 RakNet::Packet* pket){ return new AcGetBuddies(Peer , pket);}
		AcGetBuddies(RakNet::RakPeerInterface* Peer,
			 RakNet::Packet* pket) : Action(Peer , pket){}
		~AcGetBuddies(void){}
	private:
		virtual void doWork();
		virtual Common::NetMessage GetMessageID() {return Common::NETMSG_GETBUDDIES;}
	};
}
