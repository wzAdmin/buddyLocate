package com.wzAdmin.buddy;

import java.util.List;
import java.util.Map;

import com.wzAdmin.buddy.net.NetUtils;
import com.wzAdmin.buddy.utils.PhoneUtils;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

public class ContactsActivity extends Activity {
	List< Map< String , Object> > mPhoneData;
	PhoneListAdapter madapter;
	ListView mListView;
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
			final int ImageWidth = 100;
			final int ImageHeight= 100;
			final int TextSize = 80;
			if(null == convertView)
				convertView = mInflater.inflate(R.layout.contactitem, null);
			String name = (String)mPhoneData.get(position).get(PhoneUtils.NAME);
			Bitmap bitmap = (Bitmap)mPhoneData.get(position).get(PhoneUtils.IMAGE);
			if(null == bitmap){
				bitmap = Bitmap.createBitmap(ImageWidth, ImageHeight, Bitmap.Config.ARGB_8888);
				Canvas cas = new Canvas(bitmap);
				Paint pt = new Paint();
				Typeface font = Typeface.create("ËÎÌו", Typeface.BOLD);
				pt.setColor(Color.GREEN);
				pt.setTypeface(font);
				pt.setTextSize(TextSize);
				pt.setTextAlign(Paint.Align.CENTER);
				cas.drawColor(Color.BLUE);
				cas.drawText(name.substring(name.length() - 1 , name.length()), ImageWidth/2
						, TextSize, pt);
			}
			
			ImageView imv = (ImageView)convertView.findViewById(R.id.img);
			imv.setMaxHeight(ImageHeight);
			imv.setMaxWidth(ImageWidth);
			imv.setMinimumHeight(ImageHeight);
			imv.setMinimumWidth(ImageWidth);
			imv.setImageBitmap(bitmap);
			
			TextView tv = (TextView)convertView.findViewById(R.id.title);
			tv.setText(name);
			
			tv = (TextView)convertView.findViewById(R.id.info);
			tv.setText((String)mPhoneData.get(position).get(PhoneUtils.PHONE));
			
			return convertView;
		}
		
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mPhoneData = PhoneUtils.getInstance(this).getContacts();
		madapter = new PhoneListAdapter(this);
		mListView = new ListView(this);
		mListView.setAdapter(madapter);
		setContentView(mListView);
		NetUtils.getInstance(this).UploadContact();
	}
	
	
}
