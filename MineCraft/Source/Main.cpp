#include "Application.h"
#ifdef  WIN32
extern "C"
{
	//enable dedicated graphics
	__declspec(dllexport) bool NvOptimusEnablement = true;
	__declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
}
#endif //  __WIN32


int main()
{
	Application app("Minecraft");
	app.runLoop();
	return 0;
}