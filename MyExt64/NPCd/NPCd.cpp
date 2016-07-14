
#include <NPCd/NPCd.h>
#include <Common/Utils.h>

void NPCd::Init()
{
	DisableSendMail();
}

void NPCd::DisableSendMail()
{
	NOPMemory(0x42CD41, 5);
	NOPMemory(0x42CDBE, 5);
}

