#pragma once
#include "action.h"

namespace Net
{
	class AcGetBuddyLocation :
		public Common::Action
	{

	public:
		static Common::Action* Create(RakNet::RakPeerInterface* Peer,
			RakNet::Packet* pket){ return new AcGetBuddyLocation(Peer , pket);}
		AcGetBuddyLocation(RakNet::RakPeerInterface* Peer,
			RakNet::Packet* pket) : Action(Peer , pket){}
		~AcGetBuddyLocation(void){}
	private:
		virtual void doWork();
		void PlatformWork(const Common::BuddyLocation& bdl);
		virtual Common::NetMessage GetMessageID() {return Common::NETMSG_BUDDYLOCATION;}
	};
}

