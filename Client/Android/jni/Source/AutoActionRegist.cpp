/*
 * AutoActionRegist.cpp
 *
 *  Created on: 2013-5-11
 *      Author: WoodHome
 */
#include "Net/MainClient.h"
#include "Action.h"
#include "CommonType.h"
#include "Net/Action/AcMainLogin.h"
#include <jni.h>

class AutoActionRegist
{
public:
	AutoActionRegist()
	{
		Common::ActionCreater* creater = Net::MainClient::Instance().GetACCreater();
		creater->Registe(Common::NETMSG_LOGINMAIN , &Net::AcMainLogin::Create);
	}
};
static AutoActionRegist autoregiste;

JNIEnv* g_mainClienrEnv = NULL;
extern JavaVM* g_Jvm ;
namespace Net
{
	void MainClient::AttachThread()
	{
		g_Jvm->AttachCurrentThread(&g_mainClienrEnv,NULL);
	}

	void MainClient::DetachThread()
	{
		g_Jvm->DetachCurrentThread();
	}
}
