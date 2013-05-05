package com.wzAdmin.buddy.net;

import com.wzAdmin.buddy.MapActivity;
import com.wzAdmin.buddy.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.widget.TextView;

public class LoginHandler extends Handler {
	Activity mContext;
	public LoginHandler(Activity context){
		super(context.getMainLooper());
		mContext = context;
	}
    @Override  
    public void handleMessage(Message msg) {
		TextView loginfo = (TextView)mContext.findViewById(R.id.loginInfo);
    	switch(msg.what){
    	case LoginHelper.LGE_none:
    		loginfo.setText(R.string.Login);
    		mContext.startActivity(new Intent(mContext,MapActivity.class));
    		break;
    	case LoginHelper.LGE_password_incorrect:
    		loginfo.setText(R.string.pswd_incorrect);
    		break;
    	case LoginHelper.LGE_user_notexist:
    		loginfo.setText(R.string.user_notexist);
    		break;
    	}
    }
}
