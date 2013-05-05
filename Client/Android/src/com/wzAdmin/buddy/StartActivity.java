package com.wzAdmin.buddy;

import com.wzAdmin.buddy.net.LoginHandler;
import com.wzAdmin.buddy.net.LoginHelper;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class StartActivity extends Activity {
	final static int InLogin = 0;
	final static int InRegiste = 1;
	LoginHandler msghandler;
	LoginHelper mhelper;
	int mInwhich;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mInwhich = InLogin;
		setContentView(R.layout.login);
		msghandler = new LoginHandler(this);
		mhelper = new LoginHelper(msghandler);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.start, menu);
		return true;
	}
	
	@Override
	public void onContentChanged(){
		super.onContentChanged();
		if(InLogin == mInwhich){
			Button login = (Button)this.findViewById(R.id.login);
			Button reg = (Button)this.findViewById(R.id.reg);
			login.setOnClickListener(new OnClickListener(){

				@Override
				public void onClick(View arg0) {
					// TODO Auto-generated method stub
					TextView Textuser = (TextView)StartActivity.this.findViewById(R.id.user);
					TextView Textpswd = (TextView)StartActivity.this.findViewById(R.id.pswd);
					mhelper.Login(Textuser.getText().toString(), Textpswd.getText().toString());
				}
				
			});
			reg.setOnClickListener(new OnClickListener(){
				@Override
				public void onClick(View arg0) {
					// TODO Auto-generated method stub
					StartActivity.this.mInwhich = InRegiste;
					setContentView(R.layout.registe);
				}
			});
		}
		else{
			
			Button login = (Button)StartActivity.this.findViewById(R.id.login);
			login.setOnClickListener(new OnClickListener(){
				@Override
				public void onClick(View arg0) {
					// TODO Auto-generated method stub
					StartActivity.this.mInwhich = InLogin;
					setContentView(R.layout.login);
				}
				
			});
			
			
			Button reg = (Button)StartActivity.this.findViewById(R.id.reg);
			reg.setOnClickListener(new OnClickListener(){
				
				@Override
				public void onClick(View arg0) {
					// TODO Auto-generated method stub
					TextView Textuser = (TextView)StartActivity.this.findViewById(R.id.user);
					TextView Textpswd = (TextView)StartActivity.this.findViewById(R.id.pswd);
					TextView Textrepswd = (TextView)StartActivity.this.findViewById(R.id.repswd);
					if(Textpswd.getText().toString().equals(Textrepswd.getText().toString()))
						mhelper.Registe(Textuser.getText().toString(), Textpswd.getText().toString());
					else{
						TextView reginfo = (TextView)StartActivity.this.findViewById(R.id.loginInfo);
						reginfo.setText(R.string.pswd_diff);
					}
				}
			});
		}
	}
}
