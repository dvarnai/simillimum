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

#ifndef _INCLUDE_SIMILLIMUM_LuaEngine_H_
#define _INCLUDE_SIMILLIMUM_LuaEngine_H_

extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <luajit.h>
}

#include <ILuaEngine.h>

using namespace Simillimum;

class LuaEngine : public ILuaEngine
{
	int m_iLastError;
	lua_State *L;
public:
	LuaEngine();
	virtual void RegisterLibrary(const char * name, const luaL_Reg * functions);
	virtual bool LoadPlugin(const char * fullpath, int *err);
	virtual const char * GetErrorString();
	virtual const char *GetGlobalString(const char  * name);
	virtual const char * GetPluginInfo(const  char * plugin, const char  * name);
	virtual void SetGlobalNum(const char * name, int value);
	virtual bool ExecuteString(const char * string);
	virtual int GetLastError();
	virtual void GetLastErrorText(char * error, int maxlen);
	~LuaEngine()
	{
		if(L)
			lua_close(L);
	}
};

extern LuaEngine g_pLuaEngine;

#endif //_INCLUDE_SIMILLIMUM_LuaEngine_H_
