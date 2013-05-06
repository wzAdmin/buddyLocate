#include "Action.h"

namespace Common
{
	Action* ActionCreater::CreateAction( NetMessage messageID )
	{
		CreaterIt it = mCreaters.find(messageID);
		if(mCreaters.end() == it)
			return NULL;
		else
			return (*it->second)();
	}

	void ActionCreater::Registe( NetMessage id , Creater createfunc )
	{
		CreaterIt it = mCreaters.find(id);
		if(mCreaters.end() == it)
			mCreaters.insert(std::pair<NetMessage , Creater>(id , createfunc));
	}
}