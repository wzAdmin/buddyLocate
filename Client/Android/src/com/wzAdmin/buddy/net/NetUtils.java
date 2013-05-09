/**
 * 
 */
package com.wzAdmin.buddy.net;

import java.util.List;
import java.util.Map;

import com.wzAdmin.buddy.utils.PhoneUtils;

import android.content.Context;

/**
 * @author WoodHome
 *
 */
public class NetUtils {
	static NetUtils mInstance = null;
	Context mContext;
	private NetUtils(Context context){
		mContext = context;
	}
	public static NetUtils getInstance(Context context){
		if(null == mInstance){
			mInstance = new NetUtils(context);
		}
		return mInstance;
	}
	public void UploadContact(){
		List< Map< String , Object> > PhoneData = PhoneUtils.getInstance(mContext).getContacts();
		long[] contacts = new long[PhoneData.size()];
		for(int i = 0; i < contacts.length ; i++){
			String str = (String)PhoneData.get(i).get(PhoneUtils.PHONE);
			contacts[i]=Long.parseLong(str, 10);
		}
		UploadContact(contacts);
	}
	
	
	
	
	public native void UploadContact(long[] contacts);
}
