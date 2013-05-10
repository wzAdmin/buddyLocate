#include "ACUploadContacts.h"
#include "DB/ContactDB.h"
#include "Net/MainServer.h"
#include "Net/UserAdressTable.h"

namespace Net
{
	void ACUploadContacts::doWork()
	{
		RakNet::RakString Clientuser = MainServer::Instance().GetUserAdressTable()->GetUser(mpket->guid);
		Common::SendContacts sc(mpket->data , mpket->bitSize);
		for(unsigned int i = 0; i < sc.Contacts.size(); i ++)
		{
			DB::ContactDB::Insert(Clientuser.C_String(),sc.Contacts[i].C_String());
		}
	}
}
