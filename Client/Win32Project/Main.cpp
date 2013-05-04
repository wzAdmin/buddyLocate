#include "Net/LoginHelper.h"
#include <stdio.h>
int main()
{
	LoginHelper lh;
	lh.Start(1);
	lh.Login("1241313","1241215");
	char c;
	while(c = getchar())
	{
		if('q'==c)
			break;
	}
	lh.Stop();
	return 0;
}