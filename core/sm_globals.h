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

#ifndef _INCLUDE_SIMILLIMUM_GLOBALS_H_
#define _INCLUDE_SIMILLIMUM_GLOBALS_H_

/**
 * @file Contains global headers that most files in Simillimum will need.
 */

#include <sp_vm_types.h>
#include <sp_vm_api.h>
#include "sm_platform.h"
#include <IShareSys.h>

using namespace SourcePawn;
using namespace Simillimum;

class IServerPluginCallbacks;

/**
 * @brief Lists result codes possible from attempting to set a core configuration option.
 */
enum ConfigResult
{
	ConfigResult_Accept = 0,	/**< Config option was successfully set */
	ConfigResult_Reject = 1,	/**< Config option was given an invalid value and was rejected */
	ConfigResult_Ignore = 2		/**< Config option was invalid, but ignored */
};

/**
 * @brief Lists possible sources of a config option change
 */
enum ConfigSource
{
	ConfigSource_File = 0,		/**< Config option was set from config file (core.cfg) */
	ConfigSource_Console = 1,	/**< Config option was set from console command (sm config) */
};

/** 
 * @brief Any class deriving from this will be automatically initiated/shutdown by Simillimum
 */
class SMGlobalClass
{
	friend class Simillimum_Core;
	friend class SimillimumBase;
	friend class CoreConfig;
	friend class CExtensionManager;
	friend class PlayerManager;
public:
	SMGlobalClass()
	{
		m_pGlobalClassNext = SMGlobalClass::head;
		SMGlobalClass::head = this;
	}
public:
	/**
	 * @brief Called when Simillimum is initially loading
	 */
	virtual void OnSimillimumStartup(bool late)
	{
	}

	/**
	 * @brief Called after all global classes have been started up
	 */
	virtual void OnSimillimumAllInitialized()
	{
	}

	/**
	 * @brief Called after all global classes have initialized
	 */
	virtual void OnSimillimumAllInitialized_Post()
	{
	}

	/**
	 * @brief Called when Simillimum is shutting down
	 */
	virtual void OnSimillimumShutdown()
	{
	}

	/**
	 * @brief Called after Simillimum is completely shut down
	 */
	virtual void OnSimillimumAllShutdown()
	{
	}

	/**
	 * @brief Called when a core config option is changed.
	 * @note This is called once BEFORE OnSimillimumStartup() when Simillimum is loading
	 * @note It can then be called again when the 'sm config' command is used
	 */
	virtual ConfigResult OnSimillimumConfigChanged(const char *key, 
												  const char *value, 
												  ConfigSource source,
												  char *error, 
												  size_t maxlength)
	{
		return ConfigResult_Ignore;
	}

	/**
	 * @brief Called when the level changes.
	 */
	virtual void OnSimillimumLevelChange(const char *mapName)
	{
	}

	/**
	 * @brief Called when the level has activated.
	 */
	virtual void OnSimillimumLevelActivated()
	{
	}

	/**
	 * @brief Called when the level ends.
	 */
	virtual void OnSimillimumLevelEnd()
	{
	}

	/**
	 * @brief Called after plugins are loaded on mapchange.
	 */
	virtual void OnSimillimumPluginsLoaded()
	{
	}

	/**
	 * @brief Called when Simillimum receives a pointer to IServerPluginCallbacks from SourceMM
	 */
	virtual void OnSimillimumVSPReceived()
	{
	}

	/**
	 * @brief Called once all MM:S plugins are loaded.
	 */
	virtual void OnSimillimumGameInitialized()
	{
	}

	/**
	 * @brief Called when an identity is dropped (right now, extensions only)
	 */
	virtual void OnSimillimumIdentityDropped(IdentityToken_t *pToken)
	{
	}

	/**
	 * @brief Called when the server maxplayers changes
	 *
	 * @param newvalue		New maxplayers value.
	 */
	virtual void OnSimillimumMaxPlayersChanged(int newvalue)
	{
	}
public:
	SMGlobalClass *m_pGlobalClassNext;
	static SMGlobalClass *head;
};

extern ISourcePawnEngine *g_pSourcePawn;
extern ISourcePawnEngine2 *g_pSourcePawn2;
extern IdentityToken_t *g_pCoreIdent;

namespace Simillimum
{
	class IThreader;
	class ITextParsers;
}

extern IThreader *g_pThreader;
extern ITextParsers *textparsers;

#include "sm_autonatives.h"

#endif //_INCLUDE_SIMILLIMUM_GLOBALS_H_

