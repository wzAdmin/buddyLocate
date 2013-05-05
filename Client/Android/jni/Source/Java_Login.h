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

class JavaLogin : public ILoginCallBack
{
public:
	static JavaLogin* Intance();
	LoginHelper mLoginHelper;
	void SetObj(JNIEnv* env,jobject obj);
private:
	JavaLogin();
	~JavaLogin();
	virtual void OnLoginReulst(LoginError err);
	virtual void OnRegisterResult(LoginError err);
	jobject mJobj;
	JNIEnv* mEnv;
	JavaVM* mJvm;
	jmethodID mOnLoginReulstid;
	jmethodID mOnRegisterResultid;
};
#endif /* JAVA_LOGIN_H_ */
