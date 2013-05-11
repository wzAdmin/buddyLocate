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
#include "Net/Action/AcGetBuddies.h"
#include "Net/Action/AcGetBuddyLocation.h"
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
		creater->Registe(Common::NETMSG_BUDDYLOCATION , &Net::AcGetBuddyLocation::Create);
	}
};
static AutoActionRegist autoregiste;

JNIEnv* g_mainClienrEnv = NULL;
jmethodID g_SendMethodid = NULL;
jobject g_MainHadler = NULL;

jclass cls_REGetBuddy = NULL;
jclass cls_GpsInfo = NULL;
jclass cls_Buddy = NULL;
jclass cls_ReciveLocation = NULL;
extern JavaVM* g_Jvm ;

extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_net_MainClientHandler_Nativehandlerinit(JNIEnv *env, jobject obj , jobject mainhandler)
{
	g_MainHadler = env->NewGlobalRef(mainhandler);
	g_SendMethodid = env->GetMethodID(env->GetObjectClass(obj),"SendClientMessage","(Lcom/wzAdmin/buddy/net/action/IAction;)V");
	cls_REGetBuddy = (jclass)env->NewGlobalRef(env->FindClass("com/wzAdmin/buddy/net/action/REGetBuddy"));
	cls_GpsInfo = (jclass)env->NewGlobalRef( env->FindClass("com/wzAdmin/buddy/net/datatype/GpsInfo"));
	cls_Buddy = (jclass)env->NewGlobalRef(env->FindClass("com/wzAdmin/buddy/net/datatype/Buddy"));
	cls_ReciveLocation = (jclass)env->NewGlobalRef(env->FindClass("com/wzAdmin/buddy/net/action/Recivebuddylocation"));
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

	jobject CreateJavaGpsobj(const Common::GpsInfo& gps)
	{
		jobject jgps = CreateJavaObj(cls_GpsInfo);
		jfieldID field = g_mainClienrEnv->GetFieldID(cls_GpsInfo,"utcTime","J");
		g_mainClienrEnv->SetLongField(jgps,field,gps.utcTime);

		field = g_mainClienrEnv->GetFieldID(cls_GpsInfo,"Latitude","D");
		g_mainClienrEnv->SetDoubleField(jgps,field,gps.Latitude);

		field = g_mainClienrEnv->GetFieldID(cls_GpsInfo,"Longitude","D");
		g_mainClienrEnv->SetDoubleField(jgps,field,gps.Longitude);

		field = g_mainClienrEnv->GetFieldID(cls_GpsInfo,"Speed","I");
		g_mainClienrEnv->SetIntField(jgps,field,gps.Speed);

		field = g_mainClienrEnv->GetFieldID(cls_GpsInfo,"Accuracy","I");
		g_mainClienrEnv->SetIntField(jgps,field,gps.Accuracy);

		field = g_mainClienrEnv->GetFieldID(cls_GpsInfo,"Altitude","I");
		g_mainClienrEnv->SetIntField(jgps,field,gps.Altitude);

		return jgps;
	}

	jobject CreateJavaBuddy(const Common::GpsInfo& gps ,const char* uftUserid)
	{
		jobject jbuddy = CreateJavaObj(cls_Buddy);

		jobject jgps = CreateJavaGpsobj(gps);
		jfieldID field = g_mainClienrEnv->GetFieldID(cls_Buddy,"gps","Lcom/wzAdmin/buddy/net/datatype/GpsInfo;");
		g_mainClienrEnv->SetObjectField(jbuddy,field,jgps);

		jstring userid = g_mainClienrEnv->NewStringUTF(uftUserid);
		field = g_mainClienrEnv->GetFieldID(cls_Buddy,"userid","Ljava/lang/String;");
		g_mainClienrEnv->SetObjectField(jbuddy,field,userid);

		return jbuddy;
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
		jobject jregetbuddy = CreateJavaObj(cls_REGetBuddy);
		jobjectArray javabuddies = CreateJavaObjArray(cls_Buddy,buddys.BuddyCount);
		LOG_Trace(LOG_INFO,"Buddy","NativeLenth:%d\n",buddys.BuddyCount);
		for(unsigned int i = 0 ; i < buddys.BuddyCount ; i ++)
		{
			jobject jbuddy = CreateJavaBuddy(buddys.Buddies[i].gps , buddys.Buddies[i].userid.C_String());
			g_mainClienrEnv->SetObjectArrayElement(javabuddies,i,jbuddy);
		}
		jfieldID fid = g_mainClienrEnv->GetFieldID(cls_REGetBuddy,"mbuddies","[Lcom/wzAdmin/buddy/net/datatype/Buddy;");
		g_mainClienrEnv->SetObjectField(jregetbuddy,fid,javabuddies);
		SendToUIThread(jregetbuddy);
	}

	void AcGetBuddyLocation::PlatformWork(const Common::BuddyLocation& bdl)
	{
		LOG_Trace(LOG_INFO,"Buddy","Location:%s\n",bdl.userid.C_String());
		jobject jReciveLocation = CreateJavaObj(cls_ReciveLocation);
		jobject jbuddy = CreateJavaBuddy(bdl.gps,bdl.userid.C_String());

		jfieldID fid = g_mainClienrEnv->GetFieldID(cls_ReciveLocation,"bd","Lcom/wzAdmin/buddy/net/datatype/Buddy;");
		g_mainClienrEnv->SetObjectField(jReciveLocation,fid,jbuddy);

		SendToUIThread(jReciveLocation);
	}
}
