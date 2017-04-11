#include <App.h>

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }
#pragma comment(lib, "legacy_stdio_definitions.lib") 

int main(int argc, char* args[])
{

	App *app=App::Instance();
	app->Init("test", 500, 500);
	app->Start();
	return 1;
}