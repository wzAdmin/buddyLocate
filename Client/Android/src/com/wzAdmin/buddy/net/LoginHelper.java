/**
 * 
 */
package com.wzAdmin.buddy.net;

import android.app.Activity;
import android.util.Log;

/**
 * @author Administrator
 *
 */
public class LoginHelper implements ILoginCallBack {
	static{
		System.loadLibrary("Client");
	}
	Activity mContext;
	public LoginHelper(Activity context){
		mContext = context;
		SetCallBack(this);
	}
	/* (non-Javadoc)
	 * @see com.wzAdmin.buddy.net.ILoginCallBack#OnLoginResult()
	 */
	@Override
	public void OnLoginResult(int errcode) {
		// TODO Auto-generated method stub
		Log.i("Login", "errcode:"+errcode);
	}

	/* (non-Javadoc)
	 * @see com.wzAdmin.buddy.net.ILoginCallBack#OnRegistResult()
	 */
	@Override
	public void OnRegistResult(int errcode) {
		// TODO Auto-generated method stub
		
		Log.i("Login", "errcode:"+errcode);
	}

	/**
	 * native login
	 */
	public native void Login(String user , String pswd);
	
	/**
	 * native register
	 */
	public native void Registe(String user , String pswd);
	
	/**
	 * 
	 * @param cb Set callback to native
	 */
	private native void SetCallBack(ILoginCallBack cb);
}
