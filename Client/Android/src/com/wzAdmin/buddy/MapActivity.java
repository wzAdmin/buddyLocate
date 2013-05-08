package com.wzAdmin.buddy;

import com.amap.api.location.AMapLocation;
import com.amap.api.location.AMapLocationListener;
import com.amap.api.location.LocationManagerProxy;
import com.amap.api.location.LocationProviderProxy;
import com.amap.api.maps.AMap;
import com.amap.api.maps.LocationSource;
import com.amap.api.maps.SupportMapFragment;

import android.content.Intent;
import android.location.Location;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MapActivity extends FragmentActivity implements 
LocationSource, AMapLocationListener {
	private AMap aMap;
	private OnLocationChangedListener mListener;
	private LocationManagerProxy mAMapLocationManager;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.basic_demo);
		init();
	}
	
	/**
	 * 初始化AMap对象
	 */
	private void init() {
		if (aMap == null) {
			aMap = ((SupportMapFragment) getSupportFragmentManager()
					.findFragmentById(R.id.map)).getMap();
			mAMapLocationManager = LocationManagerProxy
					.getInstance(MapActivity.this);
			aMap.setLocationSource(this);
			aMap.setMyLocationEnabled(true);
			
			Button mycontact = (Button)this.findViewById(R.id.phonecantacts);
			mycontact.setOnClickListener(new OnClickListener(){

				@Override
				public void onClick(View arg0) {
					startActivity(new Intent(MapActivity.this,ContactsActivity.class));
				}
				
			});
		}
	}

	@Override
	public void onLocationChanged(Location arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onProviderDisabled(String arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onProviderEnabled(String arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onStatusChanged(String arg0, int arg1, Bundle arg2) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onLocationChanged(AMapLocation arg0) {
		// TODO Auto-generated method stub
		if(mListener != null)
			mListener.onLocationChanged(arg0);
		this.UploadGps(arg0.getTime(), (int)(arg0.getLatitude()*1000000),(int) (arg0.getLongitude() * 1000000),
				(int)arg0.getAccuracy(), (int)arg0.getAltitude(), (int)arg0.getSpeed());

	}

	@Override
	public void activate(OnLocationChangedListener arg0) {
		// TODO Auto-generated method stub
		mListener = arg0;	
		if (mAMapLocationManager == null) {
			mAMapLocationManager = LocationManagerProxy.getInstance(this);
		}
		mAMapLocationManager.requestLocationUpdates(
				LocationProviderProxy.AMapNetwork, 1000, 0, this);
	}

	@Override
	public void deactivate() {
		// TODO Auto-generated method stub
		
	}
	
	private native void UploadGps(long utcTime ,int Latitude ,int Longitude,int Accuracy,int Altitude ,int Speed);
}
