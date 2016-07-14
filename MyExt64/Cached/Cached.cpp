
#include <Cached/Cached.h>
#include <Common/Utils.h>

void Cached::Init()
{
	DisableSendMail();
}

void Cached::DisableSendMail()
{
	NOPMemory(0x4623C9, 5);
	NOPMemory(0x463066, 5);
}

