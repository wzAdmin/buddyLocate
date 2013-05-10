package com.wzAdmin.buddy.net;

public interface ILoginCallBack {
	/**
	 * 
	 * @param errcode @see LGE_
	 */
	public void OnLoginResult(int errcode);
	
	/**
	 * 
	 * @param errcode @see LGE_
	 */
	public void OnRegistResult(int errcode);
	
	public final static int LGE_none = 0;
	public final static int LGE_user_notexist = 1;
	public final static int LGE_user_existed = 2;
	public final static int LGE_password_incorrect = 3;
	public final static int LGE_cannotconnect = 4;
	public final static int LGE_unkown = 5;
}
