#pragma once
#include <map>
#include "CommonType.h"

namespace RakNet
{
	struct Packet;
	class RakPeerInterface;
}
namespace Common
{
	class Action
	{
	public:
		Action(RakNet::RakPeerInterface* Peer,
			const RakNet::Packet* pket):mPeer(Peer),mpket(pket){}
		virtual ~Action(){}
	public:
		virtual void doWork() = 0;
		virtual NetMessage GetMessageID() = 0;
	protected:
		RakNet::RakPeerInterface* mPeer;
		const RakNet::Packet* mpket;
	};

	class ActionCreater
	{
		typedef Action* (*Creater)(RakNet::RakPeerInterface* Peer,
			const RakNet::Packet* pket);
	public:
		ActionCreater(){}
		~ActionCreater(){}
		Action* CreateAction(NetMessage messageID,RakNet::RakPeerInterface* Peer,
			const RakNet::Packet* pket);
		void Registe(NetMessage id , Creater createfunc);
	private:
		std::map<NetMessage , Creater> mCreaters;
		typedef std::map<NetMessage , Creater>::iterator CreaterIt; 
	};



}