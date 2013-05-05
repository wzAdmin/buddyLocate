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
	LoginHandler msghandler;
	LoginHelper mhelper;
	TextView Textuser;
	TextView Textpswd;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_start);
		msghandler = new LoginHandler(this);
		mhelper = new LoginHelper(msghandler);
		Button btn = (Button)this.findViewById(R.id.Login);
		Textuser = (TextView)this.findViewById(R.id.user);
		Textpswd = (TextView)this.findViewById(R.id.pswd);
		btn.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				mhelper.Login(Textuser.getText().toString(), Textpswd.getText().toString());
			}
			
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.start, menu);
		return true;
	}

}
