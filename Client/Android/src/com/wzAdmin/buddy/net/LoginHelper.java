/**
 * 
 */
package com.wzAdmin.buddy.net;

import android.os.Handler;

/**
 * @author Administrator
 *
 */
public class LoginHelper implements ILoginCallBack {
	static{
		System.loadLibrary("Client");
	}
	Handler mhandler;
	public LoginHelper(Handler msghandler){
		mhandler = msghandler;
		SetCallBack(this);
	}
	/* (non-Javadoc)
	 * @see com.wzAdmin.buddy.net.ILoginCallBack#OnLoginResult()
	 */
	@Override
	public void OnLoginResult(int errcode) {
		// TODO Auto-generated method stub
		mhandler.sendMessage(mhandler.obtainMessage(errcode));
		}

	/* (non-Javadoc)
	 * @see com.wzAdmin.buddy.net.ILoginCallBack#OnRegistResult()
	 */
	@Override
	public void OnRegistResult(int errcode) {
		// TODO Auto-generated method stub
		mhandler.sendMessage(mhandler.obtainMessage(errcode));
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
