/*
 * UploadLocation.cpp
 *
 *  Created on: 2013-5-7
 *      Author: WoodHome
 */

#include <jni.h>
#include "Net/MainClient.h"
#include "RakPeerInterface.h"
#include "CommonType.h"

extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_MapActivity_UploadGps(JNIEnv *env, jobject obj ,
		jlong utcTime ,jint Latitude ,jint Longitude,jint Accuracy,jint Altitude ,jint Speed)
{
	Common::SendGps sendData;
	sendData.location.Accuracy = Accuracy;
	sendData.location.Altitude = Altitude;
	sendData.location.Latitude = Latitude;
	sendData.location.Longitude = Longitude;
	sendData.location.Speed = Speed;
	sendData.location.utcTime = utcTime;
	RakNet::BitStream bst;
	sendData.ToBitStream(bst);
	Net::MainClient::Instance().SendBitStream(&bst);
}
