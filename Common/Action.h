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
			RakNet::Packet* pket):mPeer(Peer),mpket(pket){}
		virtual ~Action(){}
	public:
		virtual void doWork() = 0;
		virtual NetMessage GetMessageID() = 0;
	private:
		RakNet::RakPeerInterface* mPeer;
		RakNet::Packet* mpket;
	};

	class ActionCreater
	{
		typedef Action* (*Creater)();
	public:
		ActionCreater(){}
		~ActionCreater(){}
		Action* CreateAction(NetMessage messageID);
		void Registe(NetMessage id , Creater createfunc);
	private:
		std::map<NetMessage , Creater> mCreaters;
		typedef std::map<NetMessage , Creater>::iterator CreaterIt; 
	};



}