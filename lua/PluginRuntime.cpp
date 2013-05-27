#include "PluginRuntime.h"

LuaPluginRuntime::LuaPluginRuntime(lua_State * l, const char * plugin)
{
	strncpy(m_szPlugin, plugin, sizeof(m_szPlugin)-1);
	snprintf(m_szInstance, sizeof(m_szInstance), "%s_instance", plugin);
	L = l;
}

LuaPluginRuntime::~LuaPluginRuntime()
{
	if(function_names.size() > 0)
	{
		SourceHook::List<char*>::iterator iter;
		for (iter=function_names.begin();
		 iter!=function_names.end();
		 iter++)
		{
			LuaPluginFunction * fn = functions.retrieve(*iter);
			if(fn)
				delete fn;
		}
	}
}

IPluginDebugInfo *LuaPluginRuntime::GetDebugInfo()
{
	return NULL;
}

int LuaPluginRuntime::FindNativeByName(const char *name, uint32_t *index)
{
	return 0;
}


int LuaPluginRuntime::GetNativeByIndex(uint32_t index, sp_native_t **native)
{
	return 0;
}


uint32_t LuaPluginRuntime::GetNativesNum()
{
	return 0;
}


int LuaPluginRuntime::FindPublicByName(const char *name, uint32_t *index)
{
	return 0;
}


int LuaPluginRuntime::GetPublicByIndex(uint32_t index, sp_public_t **publicptr)
{
	return 0;
}

uint32_t LuaPluginRuntime::GetPublicsNum()
{
	return 0;
}


int LuaPluginRuntime::GetPubvarByIndex(uint32_t index, sp_pubvar_t **pubvar)
{
	return 0;
}

int LuaPluginRuntime::FindPubvarByName(const char *name, uint32_t *index)
{
	return 0;
}

int LuaPluginRuntime::GetPubvarAddrs(uint32_t index, cell_t *local_addr, cell_t **phys_addr)
{
	return 0;
}

uint32_t LuaPluginRuntime::GetPubVarsNum()
{
	return 0;
}

IPluginFunction *LuaPluginRuntime::GetFunctionByName(const char *public_name)
{
	LuaPluginFunction * ret = NULL;
	if((ret = functions.retrieve(public_name)) == NULL)
	{
		lua_getglobal(L, m_szInstance);
		lua_getfield(L, -1, public_name);
		if(lua_isfunction(L,lua_gettop(L)))
		{
			ret = new LuaPluginFunction(this, public_name);
		}
	}
	return ret;
}

IPluginFunction *LuaPluginRuntime::GetFunctionById(funcid_t func_id)
{
	return NULL;
}

IPluginContext *LuaPluginRuntime::GetDefaultContext()
{
	return NULL;
}

bool LuaPluginRuntime::IsDebugging()
{
	return false;
}

int LuaPluginRuntime::ApplyCompilationOptions(ICompilation *co)
{
	return 0;
}
		

void LuaPluginRuntime::SetPauseState(bool paused)
{
}

bool LuaPluginRuntime::IsPaused()
{
	return false;
}

size_t LuaPluginRuntime::GetMemUsage()
{
	return 0;
}

unsigned char *LuaPluginRuntime::GetCodeHash()
{
	return 0;
}

unsigned char *LuaPluginRuntime::GetDataHash()
{
	return 0;
}