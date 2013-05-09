
package com.wzAdmin.buddy.net.action;

import android.util.Log;

import com.wzAdmin.buddy.net.datatype.Buddy;


/**
 * @ClassName: REGetBuddy
 * @Description: (处理服务器返回的Getbuddy数据)
 * @author Woodhome
 * @date 2013-5-9 下午12:51:06
 * 
 */
public class REGetBuddy implements IAction {
	Buddy[] mbuddies;
	/* (non-Javadoc)
	 * @see com.wzAdmin.buddy.net.IAction#doWrok()
	 */
	@Override
	public void doWrok() {
		// TODO Auto-generated method stub
		Log.i("Buddy","BuddyCount:" + mbuddies.length);
	}
	
}
