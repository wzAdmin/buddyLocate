#pragma once
#include "action.h"
namespace Net
{
	class ACUploadGps :
		public Common::Action
	{
	public:
		static Common::Action* Create(RakNet::RakPeerInterface* Peer,
			RakNet::Packet* pket){ return new ACUploadGps(Peer , pket);}
		ACUploadGps(RakNet::RakPeerInterface* Peer,
			RakNet::Packet* pket):Action(Peer , pket){}
		~ACUploadGps(void){}
	private:
		virtual void doWork() ;
		virtual Common::NetMessage GetMessageID() {return Common::NETMSG_SENDGPS;}
	};
}

