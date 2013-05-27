#include "PluginFunction.h"

LuaPluginFunction::LuaPluginFunction(LuaPluginRuntime * runtime, const char * function)
{
	m_nParams = 0;
	m_pRuntime = runtime;
	L = runtime->GetLuaState();
	strncpy(m_szFunction, function, sizeof(m_szFunction)-1);
}

int LuaPluginFunction::Execute(cell_t *result)
{
	lua_getglobal(L, m_pRuntime->GetPluginInstance());
	lua_getfield(L, -1, m_szFunction);
	int top = lua_gettop(L);
	lua_call(L, m_nParams, 1);
	int pop = lua_gettop(L)-top;
	if(pop != 0)
	{
		*result = (cell_t)lua_tointeger(L, -1);
		lua_pop(L, pop);
	}
	m_nParams = 0;
	return 0;
}

int LuaPluginFunction::CallFunction(const cell_t *params, unsigned int num_params, cell_t *result)
{
	return 0;
}

IPluginContext *LuaPluginFunction::GetParentContext()
{
	return 0;
}

bool LuaPluginFunction::IsRunnable()
{
	return true;
}

funcid_t LuaPluginFunction::GetFunctionID()
{
	return -1;
}

int LuaPluginFunction::Execute2(IPluginContext *ctx, cell_t *result)
{
	return Execute(result);
}

int LuaPluginFunction::CallFunction2(IPluginContext *ctx, 
	const cell_t *params, 
	unsigned int num_params, 
	cell_t *result)
{
	return 0;
}

IPluginRuntime *LuaPluginFunction::GetParentRuntime()
{
	return m_pRuntime;
}

int LuaPluginFunction::PushCell(cell_t cell)
{
	lua_pushnumber(L, cell);
	++m_nParams;
	return 0;
}


int LuaPluginFunction::PushCellByRef(cell_t *cell, int flags)
{
	lua_pushlightuserdata(L, cell);
	++m_nParams;
	return 0;
}


int LuaPluginFunction::PushFloat(float number)
{
	lua_pushnumber(L, number);
	++m_nParams;
	return 0;
}


int LuaPluginFunction::PushFloatByRef(float *number, int flags)
{
	lua_pushlightuserdata(L, number);
	++m_nParams;
	return 0;
}


int LuaPluginFunction::PushArray(cell_t *inarray, unsigned int cells, int flags)
{
	lua_pushlightuserdata(L, inarray);
	++m_nParams;
	return 0;
}

int LuaPluginFunction::PushString(const char *string)
{
	lua_pushstring(L, string);
	++m_nParams;
	return 0;
}


int LuaPluginFunction::PushStringEx(char *buffer, size_t length, int sz_flags, int cp_flags)
{
	lua_pushlstring(L, buffer, length);
	++m_nParams;
	return 0;
}

void LuaPluginFunction::Cancel()
{
	lua_pop(L, m_nParams);
}