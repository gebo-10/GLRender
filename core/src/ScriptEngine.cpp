#include <ScriptEngine.h>

ScriptEngine::ScriptEngine()
{

}

ScriptEngine::~ScriptEngine()
{
	lua_close(L);
}

bool ScriptEngine::Init()
{
	L = lua_open();
	luaL_openlibs(L);
	runing = false;
	//const char *buf = "ScriptEngine lua init \n";
	//luaL_dostring(L, buf);
	//LOG(INFO) << "ScriptEngine lua init success";
	return true;
}

bool ScriptEngine::StartGameScript()
{
	runing = true;
	return true;
}

void ScriptEngine::Update()
{
	if (!runing)
	{
		return;
	}
}

void ScriptEngine::StopGameScript()
{
	runing = false;
}
