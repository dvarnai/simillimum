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

#ifndef _INCLUDE_SIMILLIMUM_LUAPLUGINRUNTIME_H_
#define _INCLUDE_SIMILLIMUM_LUAPLUGINRUNTIME_H_

/**
 * @file IPluginSys.h
 * @brief Defines the interface for the Plugin System, which manages loaded plugins.
 */

extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <luajit.h>
}

#include <sm_platform.h>
#include <lua/lua_types.h>
#include <sp_vm_api.h>

#include <sm_trie_tpl.h>
#include <sh_list.h>

#include "PluginFunction.h"

using namespace Simillimum;
using namespace SourcePawn;

namespace Simillimum
{
	/**
	 * @brief Manages the runtime loading and unloading of plugins.
	 */
	class LuaPluginFunction;
	class LuaPluginRuntime;

	class LuaPluginRuntime : public IPluginRuntime
	{
		char m_szPlugin[PLATFORM_MAX_PATH];
		char m_szInstance[PLATFORM_MAX_PATH+9];
		lua_State * L;
		SourceHook::List<char*> function_names;
		KTrie<LuaPluginFunction> functions;
	public:
		LuaPluginRuntime(lua_State * l, const char * instance);
		~LuaPluginRuntime();

		virtual IPluginDebugInfo *GetDebugInfo();

		/**
		 * @brief Finds a native by name.
		 *
		 * @param name			Name of native.
		 * @param index			Optionally filled with native index number.
		 */
		virtual int FindNativeByName(const char *name, uint32_t *index);

		/**
		 * @brief Gets native info by index.
		 *
		 * @param index			Index number of native.
		 * @param native		Optionally filled with pointer to native structure.
		 */
		virtual int GetNativeByIndex(uint32_t index, sp_native_t **native);

		/**
		 * @brief Gets the number of natives.
		 * 
		 * @return				Filled with the number of natives.
		 */
		virtual uint32_t GetNativesNum();

		/**
		 * @brief Finds a public function by name.
		 *
		 * @param name			Name of public
		 * @param index			Optionally filled with public index number.
		 */
		virtual int FindPublicByName(const char *name, uint32_t *index);

		/**
		 * @brief Gets public function info by index.
		 * 
		 * @param index			Public function index number.
		 * @param publicptr		Optionally filled with pointer to public structure.
		 */
		virtual int GetPublicByIndex(uint32_t index, sp_public_t **publicptr);

		/**
		 * @brief Gets the number of public functions.
		 *
		 * @return				Filled with the number of public functions.
		 */
		virtual uint32_t GetPublicsNum();

		/**
		 * @brief Gets public variable info by index.
		 * 
		 * @param index			Public variable index number.
		 * @param pubvar		Optionally filled with pointer to pubvar structure.
		 */
		virtual int GetPubvarByIndex(uint32_t index, sp_pubvar_t **pubvar);

		/**
		 * @brief Finds a public variable by name.
		 *
		 * @param name			Name of pubvar
		 * @param index			Optionally filled with pubvar index number.
		 */
		virtual int FindPubvarByName(const char *name, uint32_t *index);

		/**
		 * @brief Gets the addresses of a public variable.
		 * 
		 * @param index			Index of public variable.
		 * @param local_addr		Address to store local address in.
		 * @param phys_addr		Address to store physically relocated in.
		 */
		virtual int GetPubvarAddrs(uint32_t index, cell_t *local_addr, cell_t **phys_addr);

		/**
		 * @brief Returns the number of public variables.
		 *
		 * @return				Number of public variables.
		 */
		virtual uint32_t GetPubVarsNum();

		/**
		 * @brief Returns a function by name.
		 *
		 * @param public_name		Name of the function.
		 * @return					A new IPluginFunction pointer, NULL if not found.
		 */
		virtual IPluginFunction *GetFunctionByName(const char *public_name);

		/**
		 * @brief Returns a function by its id.
		 *
		 * @param func_id			Function ID.
		 * @return					A new IPluginFunction pointer, NULL if not found.
		 */
		virtual IPluginFunction *GetFunctionById(funcid_t func_id);

		/**
		 * @brief Returns the default context.  The default context 
		 * should not be destroyed.
		 *
		 * @return					Default context pointer.
		 */
		virtual IPluginContext *GetDefaultContext();

		/**
		 * @brief Returns true if the plugin is in debug mode.
		 *
		 * @return				True if in debug mode, false otherwise.
		 */
		virtual bool IsDebugging();

		/**
		 * @brief Applies new compilation/runtime settings to the runtime code.
		 *
		 * The compilation object is destroyed once this function completes.
		 *
		 * @return				Error code (SP_ERROR_NONE on success).
		 */
		virtual int ApplyCompilationOptions(ICompilation *co);
		
		/**
		 * @brief Sets whether or not the plugin is paused (cannot be run).
		 *
		 * @param pause			Pause state.
		 */
		virtual void SetPauseState(bool paused);

		/**
		 * @brief Returns whether or not the plugin is paused (runnable).
		 *
		 * @return				Pause state (true = paused, false = not).
		 */
		virtual bool IsPaused();

		/**
		 * @brief Returns the estimated memory usage of this plugin.
		 *
		 * @return				Memory usage, in bytes.
		 */
		virtual size_t GetMemUsage();

		/**
		 * @brief Returns the MD5 hash of the plugin's P-Code.
		 *
		 * @return				16-byte buffer with MD5 hash of the plugin's P-Code.
		 */
		virtual unsigned char *GetCodeHash();
		
		/**
		 * @brief Returns the MD5 hash of the plugin's Data.
		 *
		 * @return				16-byte buffer with MD5 hash of the plugin's Data.
		 */
		virtual unsigned char *GetDataHash();

		const char * GetPluginInstance()
		{
			return m_szInstance;
		}

		const char * GetPluginName()
		{
			return m_szPlugin;
		}

		lua_State * GetLuaState()
		{
			return L;
		}
	};
}

#endif //_INCLUDE_SIMILLIMUM_LUAPLUGINRUNTIME_H_

