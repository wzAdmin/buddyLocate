package com.wzAdmin.buddy;

import com.wzAdmin.buddy.net.LoginHelper;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class StartActivity extends Activity {
	LoginHelper mhelper;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_start);
		mhelper = new LoginHelper(this);
		mhelper.Login("12414", "124");
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.start, menu);
		return true;
	}

}
