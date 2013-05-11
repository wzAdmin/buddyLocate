package com.wzAdmin.buddy;

import java.util.List;

import com.amap.api.location.AMapLocation;
import com.amap.api.location.AMapLocationListener;
import com.amap.api.location.LocationManagerProxy;
import com.amap.api.location.LocationProviderProxy;
import com.amap.api.maps.AMap;
import com.amap.api.maps.LocationSource;
import com.amap.api.maps.SupportMapFragment;
import com.amap.api.search.core.AMapException;
import com.amap.api.search.geocoder.Geocoder;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.location.Address;
import android.location.Location;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MapActivity extends FragmentActivity implements 
LocationSource, AMapLocationListener {
	private AMap aMap;
	private OnLocationChangedListener mListener;
	private LocationManagerProxy mAMapLocationManager;
	private Geocoder coder;
	AMapLocation mlocation;
	long mgpsSendTime;
	
	//上传gps到服务器的时间  1minute
	static final long SendGpsinterval = 60 * 1000;
	//gps 刷新时间 1s
	static final int FreshGpsinterval = 1 * 1000;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.basic_demo);
		init();
		mgpsSendTime =0;
	}
	
	/**
	 * 初始化AMap对象
	 */
	private void init() {
		if ( null == coder)
			coder = new Geocoder(this);
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
		mlocation = arg0;
		GpsP2P(mlocation.getTime(), (int)(mlocation.getLatitude()*1000000),(int) (mlocation.getLongitude() * 1000000),
				(int)mlocation.getAccuracy(), (int)mlocation.getAltitude(), (int)mlocation.getSpeed() );
		if(arg0.getTime() - mgpsSendTime > SendGpsinterval){
			mgpsSendTime = arg0.getTime();
		Thread t = new Thread(new Runnable() {
			public void run() {
				try {
					List<Address> address = coder
							.getFromLocation(mlocation.getLatitude(), mlocation.getLongitude(), 3);
					if (address != null && address.size() > 0) {
						Address addres = address.get(0);
						String addressName = addres.getAdminArea()
								+ addres.getSubLocality()
								+ addres.getFeatureName();
						UploadGps(mlocation.getTime(), (int)(mlocation.getLatitude()*1000000),(int) (mlocation.getLongitude() * 1000000),
								(int)mlocation.getAccuracy(), (int)mlocation.getAltitude(), (int)mlocation.getSpeed() , addressName);
					}
				} catch (AMapException e) {
					Log.i("AddressER", e.toString());
				}

			}
		});
		t.start();
		}
	}

	@Override
	public void activate(OnLocationChangedListener arg0) {
		// TODO Auto-generated method stub
		mListener = arg0;	
		if (mAMapLocationManager == null) {
			mAMapLocationManager = LocationManagerProxy.getInstance(this);
		}
		mAMapLocationManager.requestLocationUpdates(
				LocationProviderProxy.AMapNetwork, FreshGpsinterval, 0, this);
	}

	@Override
	public void deactivate() {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		///getMenuInflater().inflate(R.menu.main, menu);
		//return true;
        menu.add(0, 0, 0, R.string.menu);  
        menu.add(0, 1, 1, R.string.action_exit); 
        return super.onCreateOptionsMenu(menu);  
	}
	@Override  
    public boolean onOptionsItemSelected(MenuItem item)  
    {  
        // TODO Auto-generated method stub  
        super.onOptionsItemSelected(item);  
        switch (item.getItemId())  
        {  
            case 0:  
                promoteToExit();  
                break;  
            default:  
                break;  
        }  
        return true;  
    }  
	
	private void promoteToExit()  
    {  
        new AlertDialog.Builder(this).setTitle(R.string.menu).setMessage(  
        		R.string.menu).setNegativeButton(R.string.yes,  
                new DialogInterface.OnClickListener()  
                {  
  
                    @Override  
                    public void onClick(DialogInterface dialog, int which)  
                    {  
                        // TODO Auto-generated method stub  
  
                    }  
                }).show();  
    } 
	
	@Override 
	//后台运行方法1
	public boolean onKeyDown(int keyCode, KeyEvent event){
		if(keyCode == KeyEvent.KEYCODE_BACK){
			moveTaskToBack(true);
			return true;
		}else if(keyCode == KeyEvent.KEYCODE_MENU){
			exitSystem();  
			return true;
		}
			return super.onKeyDown(keyCode, event);
	}

	public void exitSystem()  
    {  
        new AlertDialog.Builder(this).setTitle(R.string.action_exit).setMessage(  
        		R.string.confirm).setPositiveButton(R.string.yes,  
                new DialogInterface.OnClickListener()  
                {  
  
                    @Override  
                    public void onClick(DialogInterface dialog, int which)  
                    {  
                        // TODO Auto-generated method stub  
                        finish();  
                    }  
                }).setNegativeButton(R.string.no,  
                new DialogInterface.OnClickListener()  
                {  
  
                    @Override  
                    public void onClick(DialogInterface dialog, int which)  
                    {  
                        // TODO Auto-generated method stub  
  
                    }  
                }).show();  
    } 
	
	  protected void onDestroy()  
	    {  
	        // TODO Auto-generated method stub  
	        android.os.Process.killProcess(android.os.Process.myPid());  
	        System.exit(0);  
	    }  
	
	private native void UploadGps(long utcTime ,int Latitude ,int Longitude,int Accuracy,int Altitude ,int Speed,String address);
	private native void GpsP2P(long utcTime ,int Latitude ,int Longitude,int Accuracy,int Altitude ,int Speed);
}
