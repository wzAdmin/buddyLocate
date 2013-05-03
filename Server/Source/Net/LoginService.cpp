#include "LoginService.h"

namespace Net
{
	LoginService& LoginService::Instance()
	{
		static LoginService ins;
		return ins;
	}

	LoginService::LoginService()
	{

	}

	LoginService::~LoginService()
	{

	}

	void LoginService::Start()
	{

	}

}


