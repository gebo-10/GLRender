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
	bool StartGameScript();
	void Update();
	void StopGameScript();
};
#endif
