#pragma once
#include "MessageIdentifiers.h"
#include "GpsInfo.h"
#include <vector>

using namespace RakNet;

namespace Common
{
	enum LoginError
	{
		LGE_none,
		LGE_user_notexist,
		LGE_user_existed,
		LGE_password_incorrect,
		LGE_unkown
	};
	enum NetMessage
	{
		NETMSG_BEGIN = ID_USER_PACKET_ENUM,
		NETMSG_LOGIN,
		NETMSG_LOGOUT,
		NETMSG_REGISTE,
		NETMSG_SENDGPS,
		NETMSG_GETGPS,
		NETMSG_LOGINMAIN,
		NETMSG_GETBUDDIES,
		NETMSG_GETADRESS,
		NETMSG_SENDCONTACTS,

		NETMSG_END,
	};

	typedef struct _Buddy
	{
		RakString userid;
		GpsInfo gps;
		RakNetGUID NetGuid;
		SystemAddress userAddress;
	}Buddy;
	/************************************************************************/
	/*以下是Client 和 Server 通讯的数据结构体定义 如果Client->Server的结构体名
	是StructXXX 那么默认对应的Server->Client的结构体名为REStructXXX*/
	/************************************************************************/
	typedef struct _Login 
	{
		_Login(){}
		_Login(unsigned char* data , unsigned int len)
		{
			BitStream bst(data , len , false);
			bst.IgnoreBytes(1);
			bst.Read(user);
			bst.Read(pswd);
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_LOGIN);
			bst.Write(user);
			bst.Write(pswd);
		}
		RakString user;
		RakString pswd;
	}Login;	
	typedef struct _RELogin 
	{
		_RELogin(){}
		_RELogin(unsigned char* data , unsigned int len)
		{
			RakNet::BitStream bst(data , len , false);
			bst.IgnoreBytes(1);
			bst.Read(result);
			bst.Read(MainServer);
			bst.Read(port);
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_LOGIN);
			bst.Write(result);
			bst.Write(MainServer);
			bst.Write(port);
		}
		RakString MainServer;
		unsigned short port;
		unsigned char result;
	}RELogin;

	typedef struct _Regsite 
	{
		_Regsite(){}
		_Regsite(unsigned char* data , unsigned int len)
		{
			BitStream bst(data , len , false);
			bst.IgnoreBytes(1);
			bst.Read(user);
			bst.Read(pswd);
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_REGISTE);
			bst.Write(user);
			bst.Write(pswd);
		}
		RakString user;
		RakString pswd;
	}Regsite;	
	typedef struct _RERegsite
	{
		_RERegsite(){}
		_RERegsite(unsigned char* data , unsigned int len)
		{
			RakNet::BitStream bst(data , len , false);
			bst.IgnoreBytes(1);
			bst.Read(result);
			bst.Read(MainServer);
			bst.Read(port);
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_REGISTE);
			bst.Write(result);
			bst.Write(MainServer);
			bst.Write(port);
		}
		RakString MainServer;
		unsigned short port;
		unsigned char result;
	}RERegsite;

	typedef struct _LoginMain 
	{
		_LoginMain(){}
		_LoginMain(unsigned char* data , unsigned int len)
		{
			BitStream bst(data,len,false);
			bst.IgnoreBytes(1);
			bst.Read(user);
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_LOGINMAIN);
			bst.Write(user);
		}
		RakString user;
	}LoginMain;

	typedef struct _RELoginMain 
	{
		enum LoginMainResult{Login_Success , Login_Error};
		_RELoginMain(){}
		_RELoginMain(unsigned char* data , unsigned int len)
		{
			BitStream bst(data,len,false);
			bst.IgnoreBytes(1);
			bst.Read(result);
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_LOGINMAIN);
			bst.Write(result);
		}
		unsigned char result;
	}RELoginMain;

	typedef struct _GetBuddies
	{
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_GETBUDDIES);
		}
	}GetBuddies;

	typedef struct _REGetBuddies
	{
		_REGetBuddies(){}
		_REGetBuddies(unsigned char* data , unsigned int len)
		{
			BitStream bst(data,len,false);
			bst.IgnoreBytes(1);
			Buddy bd;
			bst.Read(BuddyCount);
			for (unsigned int i  =0; i < 1 ; i++)
			{
				bst.Read(bd.userid);
				bst.Read(bd.gps);
				bst.Read(bd.NetGuid);
				bst.Read(bd.userAddress);
				Buddies.push_back(bd);
			}
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_GETBUDDIES);	
			BuddyCount = Buddies.size();
			bst.Write(BuddyCount);
			for (unsigned int i = 0 ;i < Buddies.size() ; i++)
			{
				bst.Write(Buddies[i].userid);
				bst.Write(Buddies[i].gps);
				bst.Write(Buddies[i].NetGuid);
				bst.Write(Buddies[i].userAddress);
			}
		}
		unsigned int BuddyCount;
		std::vector<Buddy> Buddies;
	}REGetBuddies;

	typedef struct _SendGps
	{
		_SendGps(){}
		_SendGps(unsigned char* data , unsigned int len)
		{
			BitStream bst(data , len , false);
			bst.IgnoreBytes(1);
			bst.Read(location);
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write((unsigned char)NETMSG_SENDGPS);
			bst.Write(location);
		}
		GpsInfo location;
	}SendGps;

	typedef struct _SendContacts 
	{
		_SendContacts(){}
		_SendContacts(unsigned char* data , unsigned int len)
		{
			BitStream bst(data , len , false);
			bst.IgnoreBytes(1);
			unsigned int count = 0;
			bst.Read(count);
			Contacts.resize(count);
			for (unsigned int i =0; i < count;i++)
			{
				bst.Read(Contacts[i]);
			}
		}
		void ToBitStream(BitStream& bst)
		{
			bst.Write(NETMSG_SENDCONTACTS);
			bst.Write(Contacts.size());
			for(unsigned int i =0 ;i < Contacts.size() ; i++)
				bst.Write(Contacts[i]);
		}
		std::vector<long long> Contacts;
	}SendContacts;
}
