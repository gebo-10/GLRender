#ifndef _LUAENGINE_HPP
#define _LUAENGINE_HPP
#pragma once
#include<Base.hpp>
extern "C"
{
#include <lua.h>  
#include <lualib.h>  
#include <lauxlib.h>  
}
class ScriptEngine
{
public:
	bool runing;
	lua_State *L;
	ScriptEngine();
	~ScriptEngine();

	bool Init();
	void CheckError(int result);
	bool StartGameScript();
	void Update();
	void StopGameScript();
	void CallGlobalFun(const char *func, const char *sig, ...);
};
#endif
