#pragma once
#include "action.h"

namespace Net
{
	class ACUploadContacts :
		public Common::Action
	{
	public:
		static Common::Action* Create(RakNet::RakPeerInterface* Peer,
			RakNet::Packet* pket){ return new ACUploadContacts(Peer , pket);}
		ACUploadContacts(RakNet::RakPeerInterface* Peer,
			RakNet::Packet* pket):Action(Peer , pket){}
		~ACUploadContacts(void){}

	private:
		virtual void doWork() ;
		virtual Common::NetMessage GetMessageID() {return Common::NETMSG_SENDCONTACTS;}
	};
}

