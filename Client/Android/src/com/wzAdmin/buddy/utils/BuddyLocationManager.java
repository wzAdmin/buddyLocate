/**
 * 
 */
package com.wzAdmin.buddy.utils;

import java.util.ArrayList;
import java.util.List;

import com.wzAdmin.buddy.net.datatype.Buddy;

/**
 * @author Woodhome
 *
 */
public class BuddyLocationManager {
	static BuddyLocationManager mIns = null;
	List<IBuddyLocationlistener> mListners;
	private BuddyLocationManager(){
		mListners = new ArrayList<IBuddyLocationlistener>();
		
	}
	public static BuddyLocationManager getInstance(){
		if(null == mIns)
			mIns = new BuddyLocationManager();
		return mIns;
	}
	public void addBudyyLocatioListner(IBuddyLocationlistener listner){
		if(!mListners.contains(listner))
			mListners.add(listner);
	}
	public void BuddyLocationChangeed(Buddy bd){
		for(int i = 0 ;i < mListners.size() ; i++){
			mListners.get(i).OnBuddyLocationChange(bd);
		}
	}
}
