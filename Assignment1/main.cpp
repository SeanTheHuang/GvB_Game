#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "gamemaster.h"

int main(int argc, char **argv)
{	
	GameMaster::Instance().Initialize();
	GameMaster::Instance().Destroy();
	_CrtDumpMemoryLeaks(); //TEMP CHECK FOR MEMORY LEAKS
	return 0;
}