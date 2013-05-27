/**
 * vim: set ts=4 sw=4 :
 * =============================================================================
 * Simillimum
 * Copyright (C) 2004-2009 AlliedModders LLC.  All rights reserved.
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

#ifndef _INCLUDE_SIMILLIMUM_LUAENGINE_INTERFACE_H_
#define _INCLUDE_SIMILLIMUM_LUAENGINE_INTERFACE_H_

/**
 * @file IPluginSys.h
 * @brief Defines the interface for the Plugin System, which manages loaded plugins.
 */

#include <IShareSys.h>
#include <lua/lua_types.h>

using namespace SourcePawn;

#define SMINTERFACE_LUAENGINE_NAME		"ILuaEngine"
#define SMINTERFACE_LUAENGINE_VERSION	1

/** Context user slot 3 is used Core for holding an IPluginContext pointer. */
#define SM_CONTEXTVAR_USER		3

namespace Simillimum
{
	/**
	 * @brief Manages the runtime loading and unloading of plugins.
	 */
	class ILuaEngine : public SMInterface
	{
	public:
		virtual const char *GetInterfaceName()
		{
			return SMINTERFACE_LUAENGINE_NAME;
		}

		virtual unsigned int GetInterfaceVersion()
		{
			return SMINTERFACE_LUAENGINE_VERSION;
		}
	public:
		virtual void RegisterLibrary(const char * name, const luaL_Reg * functions) = 0;
		virtual IPluginRuntime * LoadPlugin(const char * fullpath, int *err) = 0;
		virtual const char * GetErrorString() = 0;
		virtual const char *GetGlobalString(const char  * name) = 0;
		virtual const char * GetPluginInfo(const  char * plugin, const char  * name) = 0;
		virtual void SetGlobalNum(const char * name, int value) = 0;
		virtual bool ExecuteString(const char * string) = 0;
		virtual int GetLastError() = 0;
		virtual void GetLastErrorText(char * error, int maxlen) = 0;
	};
}

#endif //_INCLUDE_SIMILLIMUM_LUAENGINE_INTERFACE_H_

