package com.wzAdmin.buddy;

import com.amap.api.location.AMapLocation;
import com.amap.api.location.AMapLocationListener;
import com.amap.api.location.LocationManagerProxy;
import com.amap.api.location.LocationProviderProxy;
import com.amap.api.maps.AMap;
import com.amap.api.maps.LocationSource;
import com.amap.api.maps.SupportMapFragment;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.location.Location;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
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
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.basic_demo);
		init();
	}
	
	/**
	 * ��ʼ��AMap����
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
	//��̨���з���1
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
	
	private native void UploadGps(long utcTime ,int Latitude ,int Longitude,int Accuracy,int Altitude ,int Speed);
}
