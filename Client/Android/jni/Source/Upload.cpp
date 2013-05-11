/*
 * Upload.cpp
 *
 *  Created on: 2013-5-7
 *      Author: WoodHome
 */

#include <jni.h>
#include "Net/MainClient.h"
#include "RakPeerInterface.h"
#include "CommonType.h"
#include "Trace.h"
#include <stdlib.h>

extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_MapActivity_UploadGps(JNIEnv *env, jobject obj ,
		jlong utcTime ,jint Latitude ,jint Longitude,jint Accuracy,jint Altitude ,jint Speed,jstring address)
{
	static long long LastuploadTime = 0;
	if(utcTime - LastuploadTime < 1000)
		return;
	LastuploadTime = utcTime;
	Common::SendGps sendData;
	sendData.location.Accuracy = Accuracy;
	sendData.location.Altitude = Altitude;
	sendData.location.Latitude = Latitude;
	sendData.location.Longitude = Longitude;
	sendData.location.Speed = Speed;
	sendData.location.utcTime = utcTime;
	const char* utfaddress= env->GetStringUTFChars(address , 0);
	sendData.location.Address = utfaddress;
	env->ReleaseStringUTFChars(address , utfaddress);
	RakNet::BitStream bst;
	sendData.ToBitStream(bst);
	Net::MainClient::Instance().SendBitStream(&bst);
}

extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_net_NetUtils_UploadContact(JNIEnv *env, jobject obj ,
		jobjectArray contacts )
{
	int length = env->GetArrayLength(contacts);
	Common::SendContacts sc;
	char name[64]={0};
	for(int i = 0 ;i < length ; i ++)
	{
		jstring name= (jstring) env->GetObjectArrayElement(contacts , i);
		const char* utfname = env->GetStringUTFChars(name , 0);
		sc.Contacts.push_back(utfname);
		env->ReleaseStringUTFChars(name , utfname);
	}
	RakNet::BitStream bst;
	sc.ToBitStream(bst);

	LOG_Trace(LOG_INFO,"UPLOAD","Length :%d\n",length);
	Net::MainClient::Instance().SendBitStream(&bst);
}
