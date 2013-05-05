#pragma once

#include "CommonType.h"

using namespace Common;

class ILoginCallBack
{
public:
	virtual ~ILoginCallBack(){}
	virtual void OnLoginReulst(LoginError err) = 0;
	virtual void OnRegisterResult(LoginError err) = 0;
};
