
package com.wzAdmin.buddy.net.action;

import android.util.Log;

import com.wzAdmin.buddy.net.datatype.Buddy;


/**
 * @ClassName: REGetBuddy
 * @Description: (������������ص�Getbuddy����)
 * @author Woodhome
 * @date 2013-5-9 ����12:51:06
 * 
 */
public class REGetBuddy implements IAction {
	Buddy[] mbuddies;
	/* (non-Javadoc)
	 * @see com.wzAdmin.buddy.net.IAction#doWrok()
	 */
	@Override
	public void doWrok() {
		// TODO ��ȡ��������Ϣ��ľ������
		Log.i("Buddy","BuddyCount:" + mbuddies.length);
	}
	
}
