#include <ScriptEngine.h>
#include <LuaPort.h>
#include <stdarg.h>
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

	tolua_Student_open(L); 

	runing = false;
	//const char *buf = "ScriptEngine lua init \n";
	//luaL_dostring(L, buf);
	//LOG(INFO) << "ScriptEngine lua init success";

	
	return true;
}

void ScriptEngine::CheckError(int result)
{
	if (result != 0)
	{
		const char * err = lua_tostring(L, -1);
		LOG(ERROR) << err << endl;
	}
}

bool ScriptEngine::StartGameScript()
{
	runing = true;


	CheckError(luaL_dofile(L, "Config.lua"));
	CheckError(luaL_dofile(L, "Assets\\Lua\\main.lua"));

	CallGlobalFun("Start", "");
	return true;
}

void ScriptEngine::Update()
{
	if (!runing)
	{
		return;
	}
	CallGlobalFun("Update", "");

}

void ScriptEngine::StopGameScript()
{
	CallGlobalFun("Stop", "");
	runing = false;
}


void ScriptEngine::CallGlobalFun(const char *func, const char *sig, ...) {
	va_list vl;
	int narg, nres; /* number of arguments and results */
	va_start(vl, sig);
	lua_getglobal(L, func); /* get function */
							/* push arguments */
	narg = 0;
	while (*sig) { /* push arguments */
		switch (*sig++) {
		case 'd': /* double argument */
			lua_pushnumber(L, va_arg(vl, double));
			break;
		case 'i': /* int argument */
			lua_pushnumber(L, va_arg(vl, int));
			break;
		case 's': /* string argument */
			lua_pushstring(L, va_arg(vl, char *));
			break;
		case '>':
			goto endwhile;
		default:
			LOG(ERROR) << "invalid option" << *(sig - 1) << endl;
		}
		narg++;
		luaL_checkstack(L, 1, "too many arguments");
	} endwhile:
	/* do the call */
	nres = strlen(sig); /* number of expected results */
	CheckError(lua_pcall(L, narg, nres, 0) );
	/* retrieve results */
	nres = -nres; /* stack index of first result */
	while (*sig) { /* get results */
		switch (*sig++) {
		case 'd': /* double result */
			if (!lua_isnumber(L, nres))
				LOG(ERROR) << "wrong result type" << endl;
			*va_arg(vl, double *) = lua_tonumber(L, nres);
			break;
		case 'i': /* int result */
			if (!lua_isnumber(L, nres))
				LOG(ERROR) << "wrong result type" << endl;
			*va_arg(vl, int *) = (int)lua_tonumber(L, nres);
			break;
		case 's': /* string result */
			if (!lua_isstring(L, nres))
				LOG(ERROR) << "wrong result type" << endl;
			*va_arg(vl, const char **) = lua_tostring(L, nres);
			break;
		default:
			LOG(ERROR)<< "invalid option"<<*(sig - 1) <<endl;
		}
		nres++;
	}
	va_end(vl);
}
