package com.wzAdmin.buddy;

import java.util.List;
import java.util.Map;

import com.wzAdmin.buddy.utils.PhoneUtils;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;

public class ContactsActivity extends Activity {
	List< Map< String , Object> > mPhoneData;
	
	public final class PhoneListAdapter extends BaseAdapter{
		private LayoutInflater mInflater;
		public PhoneListAdapter(Context context){
			mInflater = LayoutInflater.from(context);
		}
		@Override
		public int getCount() {
			return ContactsActivity.this.mPhoneData.size();
		}

		@Override
		public Object getItem(int position) {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public long getItemId(int position) {
			// TODO Auto-generated method stub
			return 0;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			convertView = mInflater.inflate(R.layout.basic_demo, null);
			return convertView;
		}
		
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mPhoneData = PhoneUtils.getInstance(this).getContacts();
	}
	
	
}
