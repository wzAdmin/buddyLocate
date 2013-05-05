/*
 * Java_Login.cpp
 *
 *  Created on: 2013-5-4
 *      Author: Administrator
 */
#include "Java_Login.h"
#include "android/log.h"

JavaLogin* g_LoginInstance = NULL;
JNIEnv* g_Env = NULL;
JavaVM* g_Jvm = NULL;
extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	g_Jvm = vm;
	vm->GetEnv((void**)&g_Env,JNI_VERSION_1_6);
	return JNI_VERSION_1_6 ;
}
extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_net_LoginHelper_Login(JNIEnv *env, jobject obj , jstring user ,jstring pswd)
{
	const char* utfuser = env->GetStringUTFChars(user , 0);
	const char* utfpswd = env->GetStringUTFChars(pswd , 0);
	JavaLogin::Intance()->mLoginHelper.Login(utfuser , utfpswd);
	env->ReleaseStringUTFChars(user , utfuser);
	env->ReleaseStringUTFChars(pswd , utfpswd);
}

extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_net_LoginHelper_Registe(JNIEnv *env, jobject obj , jstring user ,jstring pswd)
{
	const char* utfuser = env->GetStringUTFChars(user , 0);
	const char* utfpswd = env->GetStringUTFChars(pswd , 0);
	JavaLogin::Intance()->mLoginHelper.Register(utfuser , utfpswd);
	env->ReleaseStringUTFChars(user , utfuser);
	env->ReleaseStringUTFChars(pswd , utfpswd);
}

extern "C" JNIEXPORT void JNICALL Java_com_wzAdmin_buddy_net_LoginHelper_SetCallBack(JNIEnv *env, jobject obj ,jobject cb)
{
	JavaLogin::Intance()->SetObj(env , cb);
}

JavaLogin::JavaLogin() : mJobj(NULL) , mEnv(NULL),mJvm(NULL),
		mOnLoginReulstid(NULL),mOnRegisterResultid(NULL)
{
	mLoginHelper.SetCallBack(this);
	mLoginHelper.Start(1);
}

JavaLogin::~JavaLogin()
{
	if(mJobj)
		mEnv->DeleteGlobalRef(mJobj);
}

void JavaLogin::SetObj(JNIEnv* env ,jobject obj)
{
	mEnv = env;
	mJobj = mEnv->NewGlobalRef(obj);
	mEnv->GetJavaVM(&mJvm);

	jclass jcls = mEnv->GetObjectClass(mJobj);
	mOnLoginReulstid = mEnv->GetMethodID(jcls,"OnLoginResult","(I)V");
	mOnRegisterResultid = mEnv->GetMethodID(jcls,"OnRegistResult","(I)V");
}
void JavaLogin::OnLoginReulst(LoginError err)
{
	JNIEnv* env = NULL;

	mJvm->AttachCurrentThread(&env,NULL);

	env->CallVoidMethod(mJobj,mOnLoginReulstid,(int)err);

	mJvm->DetachCurrentThread();
}
void JavaLogin::OnRegisterResult(LoginError err)
{
	JNIEnv* env = NULL;

	mJvm->AttachCurrentThread(&env,NULL);

	env->CallVoidMethod(mJobj,mOnRegisterResultid,(int)err);

	mJvm->DetachCurrentThread();
}

JavaLogin* JavaLogin::Intance()
{
	if(!g_LoginInstance)
		g_LoginInstance = new JavaLogin;
	return g_LoginInstance;
}


