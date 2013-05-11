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
#include"Net/Action/AcGetBuddies.h"
#include <jni.h>
#include "Trace.h"

class AutoActionRegist
{
public:
	AutoActionRegist()
	{
		Common::ActionCreater* creater = Net::MainClient::Instance().GetACCreater();
		creater->Registe(Common::NETMSG_LOGINMAIN , &Net::AcMainLogin::Create);
		creater->Registe(Common::NETMSG_GETBUDDIES , &Net::AcGetBuddies::Create);
	}
};
static AutoActionRegist autoregiste;

JNIEnv* g_mainClienrEnv = NULL;
jmethodID g_SendMethodid = NULL;
jobject g_MainHadler = NULL;

jclass lcs_REGetBuddy = NULL;
jclass lcs_GpsInfo = NULL;
jclass lcs_Buddy = NULL;
extern JavaVM* g_Jvm ;

extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_net_MainClientHandler_Nativehandlerinit(JNIEnv *env, jobject obj , jobject mainhandler)
{
	g_MainHadler = env->NewGlobalRef(mainhandler);
	g_SendMethodid = env->GetMethodID(env->GetObjectClass(obj),"SendClientMessage","(Lcom/wzAdmin/buddy/net/action/IAction;)V");
	lcs_REGetBuddy = (jclass)env->NewGlobalRef(env->FindClass("com/wzAdmin/buddy/net/action/REGetBuddy"));
	lcs_GpsInfo = (jclass)env->NewGlobalRef( env->FindClass("com/wzAdmin/buddy/net/datatype/GpsInfo"));
	lcs_Buddy = (jclass)env->NewGlobalRef(env->FindClass("com/wzAdmin/buddy/net/datatype/Buddy"));

}
namespace Net
{
	jobject CreateJavaObj(jclass cls )
	{
		jmethodID mid = g_mainClienrEnv->GetMethodID(cls, "<init>", "()V");
		jobject obj =  g_mainClienrEnv->NewObject(cls,mid);
		return obj;
	}

	jobjectArray CreateJavaObjArray(jclass cls , int length)
	{
		jobjectArray obj =  g_mainClienrEnv->NewObjectArray(length,cls,NULL);
		return obj;
	}

	void SendToUIThread(jobject obj)
	{
		g_mainClienrEnv->CallVoidMethod(g_MainHadler , g_SendMethodid ,obj);
	}

	void MainClient::AttachThread()
	{
		g_Jvm->AttachCurrentThread(&g_mainClienrEnv,NULL);
	}

	void MainClient::DetachThread()
	{
		g_Jvm->DetachCurrentThread();
	}

	void AcGetBuddies::PlatformWork(const Common::REGetBuddies& buddys)
	{
		jobject jregetbuddy = CreateJavaObj(lcs_REGetBuddy);
		jobjectArray javabuddies = CreateJavaObjArray(lcs_Buddy,buddys.Buddies.size());
		LOG_Trace(LOG_INFO,"Buddy","NativeLenth:%d\n",buddys.Buddies.size());
		for(unsigned int i = 0 ; i < buddys.Buddies.size() ; i ++)
		{
			jobject jbuddy = CreateJavaObj(lcs_Buddy);

			jobject jgps = CreateJavaObj(lcs_GpsInfo);
			jfieldID field = g_mainClienrEnv->GetFieldID(lcs_GpsInfo,"utcTime","J");
			g_mainClienrEnv->SetLongField(jgps,field,buddys.Buddies[i].gps.utcTime);

			field = g_mainClienrEnv->GetFieldID(lcs_GpsInfo,"Latitude","D");
			g_mainClienrEnv->SetDoubleField(jgps,field,buddys.Buddies[i].gps.Latitude);

			field = g_mainClienrEnv->GetFieldID(lcs_GpsInfo,"Longitude","D");
			g_mainClienrEnv->SetDoubleField(jgps,field,buddys.Buddies[i].gps.Longitude);

			field = g_mainClienrEnv->GetFieldID(lcs_GpsInfo,"Speed","I");
			g_mainClienrEnv->SetIntField(jgps,field,buddys.Buddies[i].gps.Speed);

			field = g_mainClienrEnv->GetFieldID(lcs_GpsInfo,"Accuracy","I");
			g_mainClienrEnv->SetIntField(jgps,field,buddys.Buddies[i].gps.Accuracy);

			field = g_mainClienrEnv->GetFieldID(lcs_GpsInfo,"Altitude","I");
			g_mainClienrEnv->SetIntField(jgps,field,buddys.Buddies[i].gps.Altitude);


			field = g_mainClienrEnv->GetFieldID(lcs_Buddy,"gps","Lcom/wzAdmin/buddy/net/datatype/GpsInfo;");
			g_mainClienrEnv->SetObjectField(jbuddy,field,jgps);

			g_mainClienrEnv->SetObjectArrayElement(javabuddies,i,jbuddy);
		}
		jfieldID fid = g_mainClienrEnv->GetFieldID(lcs_REGetBuddy,"mbuddies","[Lcom/wzAdmin/buddy/net/datatype/Buddy;");
		g_mainClienrEnv->SetObjectField(jregetbuddy,fid,javabuddies);
		SendToUIThread(jregetbuddy);
	}
}
