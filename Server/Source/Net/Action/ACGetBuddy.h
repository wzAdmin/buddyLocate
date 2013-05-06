#pragma once
#include "action.h"

namespace Net
{
	class ACGetBuddy :
		public Common::Action
	{
	public:
		static Common::Action* Create(RakNet::RakPeerInterface* Peer,
			const RakNet::Packet* pket){ return new ACGetBuddy(Peer , pket);}
		ACGetBuddy(RakNet::RakPeerInterface* Peer,
			const RakNet::Packet* pket):Action(Peer , pket){}
		~ACGetBuddy(void);
	private:
		virtual void doWork() ;
		virtual Common::NetMessage GetMessageID() {return Common::NETMSG_GETBUDDIES;}
	};
}

