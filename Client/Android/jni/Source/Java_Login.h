/*
 * Java_Login.h
 *
 *  Created on: 2013-5-4
 *      Author: Administrator
 */

#ifndef JAVA_LOGIN_H_
#define JAVA_LOGIN_H_
#include<jni.h>
#include"Net/LoginCallBack.h"
#include"Net/LoginHelper.h"

class JavaLogin : public Net::LoginHelper ,public ILoginCallBack
{
public:
	static JavaLogin* Intance();
	void SetObj(JNIEnv* env,jobject obj);
private:
	JavaLogin();
	~JavaLogin();
	virtual void OnLoginReulst(LoginError err);
	virtual void OnRegisterResult(LoginError err);
	virtual void OnServiceStart();
	virtual void OnServiceStop();
	jobject mJobj;
	JNIEnv* mEnv;
	JNIEnv* mthreadEnv;
	JavaVM* mJvm;
	jmethodID mOnLoginReulstid;
	jmethodID mOnRegisterResultid;
};
#endif /* JAVA_LOGIN_H_ */
