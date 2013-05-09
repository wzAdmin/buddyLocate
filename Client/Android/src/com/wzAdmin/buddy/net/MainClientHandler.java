
package com.wzAdmin.buddy.net;

import com.wzAdmin.buddy.net.action.IAction;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * @ClassName: MainClientHandler
 * @Description: ����ײ�C++ͨѶ�߳̽�������
 * @author WoodHome
 * @date 2013-5-9 ����01:10:18
 * 
 */
public class MainClientHandler extends Handler {
	Context mContext;
	static MainClientHandler mInstance = null;
	private MainClientHandler(Context context){
		super(context.getMainLooper());
		mContext = context;
		Nativehandlerinit(this);
	}
	static public void initInatance(Context context){
		if(null != mInstance ){
			Log.i("MainHadler", "MainHandler already inited!");
		}
		else{
			mInstance = new MainClientHandler(context);
		}
	}
	static public MainClientHandler getInstacne(){
		if(null == mInstance ){
			Log.e("MainHadler", "MainHandler must init first!");
		}
		return mInstance;
	}
	
    @Override  
    public void handleMessage(Message msg) {
    	IAction ac = (IAction)msg.obj;
    	if(null != ac)
    		ac.doWrok();
    }
    
    /**
     * 
    * @Title: SendClientMessage
    * @Description: �������ֻ�ṩ���ײ�C++����
    * @param @param ac    �趨�ļ�
    * @return void    ��������
    * @throws
     */
    public void SendClientMessage(IAction ac){
    	this.sendMessage(this.obtainMessage(0, ac));
    }
    
    /**
     * 
    * @Title: Nativehandlerinit
    * @Description: ��ʼ��native handler
    * @param @param mainhandler    �趨�ļ�
    * @return void    ��������
    * @throws
     */
    private native void Nativehandlerinit(MainClientHandler mainhandler);
}
