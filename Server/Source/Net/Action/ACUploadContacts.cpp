#include "ACUploadContacts.h"

namespace Net
{
	void ACUploadContacts::doWork()
	{
		Common::SendContacts sc(mpket->data , mpket->bitSize);
		for(unsigned int i = 0; i < sc.Contacts.size(); i ++)
			printf("%ll\n",sc.Contacts[i]);
		// TODO there need do the actually things
	}
}
