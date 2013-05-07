#include "SimpleMutex.h"

namespace Common
{
	class AutoMutex
	{
	public:
		AutoMutex(RakNet::SimpleMutex* mutex)
		{
			mMutex = mutex;
			mMutex->Lock();
		}
		~AutoMutex()
		{
			mMutex->Unlock();
		}
	private:
		RakNet::SimpleMutex* mMutex;
	};
}