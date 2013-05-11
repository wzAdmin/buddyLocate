
package com.wzAdmin.buddy.net.action;

import android.util.Log;

import com.wzAdmin.buddy.net.datatype.Buddy;
import com.wzAdmin.buddy.utils.BuddyLocationManager;

/**
 * @ClassName: Recivebuddylocation
 * @Description: 收到好友定位信息后的处理
 * @author woodhome
 * @date 2013-5-9 下午04:54:40
 * 
 */
public class Recivebuddylocation implements IAction {
	Buddy bd;
	/* (non-Javadoc)
	 * @see com.wzAdmin.buddy.net.action.IAction#doWrok()
	 */
	@Override
	public void doWrok() {
		// TODO 收到好友定位信息后的处理
		Log.i("Buddy","ReciveBuddy,User:" + bd.userid + "Time:" + bd.gps.utcTime);
		BuddyLocationManager.getInstance().BuddyLocationChangeed(bd);
	}

}
