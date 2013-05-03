#pragma once
#include "MessageIdentifiers.h"

namespace Common
{
	enum LoginError
	{
		LGE_none,
		LGE_user_notexsit,
		LGE_user_exsited,
		LGE_password_incorrect,
		LGE_unkown
	};
	enum NetMessage
	{
		NETMSG_LOGIN = ID_USER_PACKET_ENUM,
		NETMSG_LOGOUT,
		NETMSG_REGISTE,
		NETMSG_SENDGPS
	};
}