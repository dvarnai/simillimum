/**
 * vim: set ts=4 :
 * =============================================================================
 * Simillimum
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.simillimum.net/license.php>.
 *
 * Version: $Id$
 */

#include <LuaSys.h>
#include "sm_platform.h"
#include "sm_stringutil.h"

#include "Logger.h"

LuaSystem g_pLuaSys;

using namespace Simillimum;

LuaSystem::LuaSystem()
{
	L = lua_open();
    luaL_openlibs(L);
}

void LuaSystem::RegisterLibrary(const char * name, const luaL_Reg * functions)
{
	luaL_register(L, name, functions);
}

bool LuaSystem::LoadPlugin(const char * fullpath, int *err)
{
	if ((*err=luaL_loadfile(L, fullpath)) || lua_pcall(L, 0, 0, 0))
        return false;

	char m_szFilename[PLATFORM_MAX_PATH];
	const char * m_szFile = fullpath;
	for(int i=strlen(fullpath);i>=0;--i)
		if(fullpath[i] == '/' || fullpath[i] == '\\')
		{
			m_szFile = fullpath+i+1;
			break;
		}

	strncpy(m_szFilename, m_szFile, sizeof(m_szFilename)-1);
	for(int i=strlen(m_szFilename);i>=0;--i)
		if(m_szFilename[i] == '.')
		{
			m_szFilename[i] = 0;
			break;
		}

	char m_szLoadLine[1024];
	UTIL_Format(m_szLoadLine, sizeof(m_szLoadLine), "%s_instance=%s.info()\n", m_szFilename, m_szFilename);
	luaL_dostring(L, m_szLoadLine);

    return true;
}

const char * LuaSystem::GetErrorString()
{
	return lua_tostring(L, -1);
}

const char * LuaSystem::GetGlobalString(const char  * name)
{
	lua_getglobal(L, name);
	return lua_tostring(L, -1);
}

const char * LuaSystem::GetPluginInfo(const  char * plugin, const char  * name)
{
	char m_szCode[1024];
	UTIL_Format(m_szCode, sizeof(m_szCode), "return %s_instance.%s", plugin, name);
	int error = luaL_dostring(L, m_szCode);
	if (error)
	{
		g_Logger.LogError("LUA ERROR: %s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	return lua_tostring(L, -1);
}

void LuaSystem::SetGlobalNum(const char * name, int value)
{
	lua_pushnumber(L, value);
	lua_setglobal(L, name);
}

bool LuaSystem::ExecuteString(const char * string)
{
	int error = luaL_dostring(L, string);
	if (error)
	{
		g_Logger.LogError("LUA ERROR: %s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	return !error;
}