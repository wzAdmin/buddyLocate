
package com.wzAdmin.buddy.net;

import com.wzAdmin.buddy.net.action.IAction;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * @ClassName: MainClientHandler
 * @Description: 处理底层C++通讯线程接收数据
 * @author WoodHome
 * @date 2013-5-9 下午01:10:18
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
    * @Description: 这个函数只提供给底层C++调用
    * @param @param ac    设定文件
    * @return void    返回类型
    * @throws
     */
    public void SendClientMessage(IAction ac){
    	this.sendMessage(this.obtainMessage(0, ac));
    }
    
    /**
     * 
    * @Title: Nativehandlerinit
    * @Description: 初始化native handler
    * @param @param mainhandler    设定文件
    * @return void    返回类型
    * @throws
     */
    private native void Nativehandlerinit(MainClientHandler mainhandler);
}
