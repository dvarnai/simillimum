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

#include "simillimum.h"
#include "sourcemm_api.h"
#include <simillimum_version.h>
#include "Logger.h"
#include "concmd_cleaner.h"
#include "compat_wrappers.h"
#include "logic_bridge.h"

Simillimum_Core g_Simillimum_Core;
IVEngineServer *engine = NULL;
IServerGameDLL *gamedll = NULL;
IServerGameClients *serverClients = NULL;
ISmmPluginManager *g_pMMPlugins = NULL;
CGlobalVars *gpGlobals = NULL;
ICvar *icvar = NULL;
IGameEventManager2 *gameevents = NULL;
IUniformRandomStream *engrandom = NULL;
CallClass<IVEngineServer> *enginePatch = NULL;
CallClass<IServerGameDLL> *gamedllPatch = NULL;
IPlayerInfoManager *playerinfo = NULL;
IBaseFileSystem *basefilesystem = NULL;
IEngineSound *enginesound = NULL;
IServerPluginHelpers *serverpluginhelpers = NULL;
IServerPluginCallbacks *vsp_interface = NULL;
int vsp_version = 0;

PLUGIN_EXPOSE(Simillimum, g_Simillimum_Core);

bool Simillimum_Core::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	GET_V_IFACE_ANY(GetServerFactory, gamedll, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
	GET_V_IFACE_CURRENT(GetServerFactory, serverClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
	GET_V_IFACE_CURRENT(GetEngineFactory, icvar, ICvar, CVAR_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, gameevents, IGameEventManager2, INTERFACEVERSION_GAMEEVENTSMANAGER2);
	GET_V_IFACE_CURRENT(GetEngineFactory, engrandom, IUniformRandomStream, VENGINE_SERVER_RANDOM_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetFileSystemFactory, basefilesystem, IBaseFileSystem, BASEFILESYSTEM_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, enginesound, IEngineSound, IENGINESOUND_SERVER_INTERFACE_VERSION);
#if SOURCE_ENGINE != SE_DOTA
	GET_V_IFACE_CURRENT(GetEngineFactory, serverpluginhelpers, IServerPluginHelpers, INTERFACEVERSION_ISERVERPLUGINHELPERS);
#endif

	/* :TODO: Make this optional and... make it find earlier versions [?] */
	GET_V_IFACE_CURRENT(GetServerFactory, playerinfo, IPlayerInfoManager, INTERFACEVERSION_PLAYERINFOMANAGER);

	if ((g_pMMPlugins = (ISmmPluginManager *)g_SMAPI->MetaFactory(MMIFACE_PLMANAGER, NULL, NULL)) == NULL)
	{
		if (error)
		{
			snprintf(error, maxlen, "Unable to find interface %s", MMIFACE_PLMANAGER);
		}
		return false;
	}

	gpGlobals = ismm->GetCGlobals();
	
	ismm->AddListener(this, this);

#if defined METAMOD_PLAPI_VERSION || PLAPI_VERSION >= 11
	if ((vsp_interface = g_SMAPI->GetVSPInfo(&vsp_version)) == NULL)
#endif
	{
		g_SMAPI->EnableVSPListener();
	}

	return g_Simillimum.InitializeSimillimum(error, maxlen, late);
}

bool Simillimum_Core::Unload(char *error, size_t maxlen)
{
	g_Simillimum.CloseSimillimum();
	return true;
}

bool Simillimum_Core::Pause(char *error, size_t maxlen)
{
	return true;
}

bool Simillimum_Core::Unpause(char *error, size_t maxlen)
{
	return true;
}

void Simillimum_Core::AllPluginsLoaded()
{
	g_Simillimum.AllPluginsLoaded();
}

const char *Simillimum_Core::GetAuthor()
{
	return "The Simillimum Team, AlliedModders LLC";
}

const char *Simillimum_Core::GetName()
{
	return "Simillimum";
}

const char *Simillimum_Core::GetDescription()
{
	return "Fork of the popular SourceMod system";
}

const char *Simillimum_Core::GetURL()
{
	return "http://www.simillimum.net/";
}

const char *Simillimum_Core::GetLicense()
{
	return "See LICENSE.txt";
}

const char *Simillimum_Core::GetVersion()
{
	return SM_VERSION_STRING;
}

const char *Simillimum_Core::GetDate()
{
	return __DATE__;
}

const char *Simillimum_Core::GetLogTag()
{
	return "SM";
}

void Simillimum_Core::OnVSPListening(IServerPluginCallbacks *iface)
{
	/* This shouldn't happen */
	if (!iface)
	{
		g_Logger.LogFatal("Metamod:Source version is out of date. Simillimum requires 1.4.2 or greater.");
		return;
	}

	if (vsp_interface == NULL)
	{
		vsp_interface = iface;
	}

	if (!g_Loaded)
	{
		return;
	}

#if defined METAMOD_PLAPI_VERSION || PLAPI_VERSION >= 11
	if (vsp_version == 0)
	{
		g_SMAPI->GetVSPInfo(&vsp_version);
	}
#else
	if (vsp_version == 0)
	{
		if (strcmp(g_Simillimum.GetGameFolderName(), "ship") == 0)
		{
			vsp_version = 1;
		}
		else
		{
			vsp_version = 2;
		}
	}
#endif

	/* Notify! */
	SMGlobalClass *pBase = SMGlobalClass::head;
	while (pBase)
	{
		pBase->OnSimillimumVSPReceived();
		pBase = pBase->m_pGlobalClassNext;
	}
}

#if defined METAMOD_PLAPI_VERSION || PLAPI_VERSION >= 11

void Simillimum_Core::OnUnlinkConCommandBase(PluginId id, ConCommandBase *pCommand)
{
#if SOURCE_ENGINE < SE_ORANGEBOX
	Global_OnUnlinkConCommandBase(pCommand);
#endif
}

#else

void Simillimum_Core::OnPluginUnload(PluginId id)
{
	Global_OnUnlinkConCommandBase(NULL);
}

#endif

void *Simillimum_Core::OnMetamodQuery(const char *iface, int *ret)
{
	void *ptr = NULL;

	if (strcmp(iface, SIMILLIMUM_INTERFACE_EXTENSIONS) == 0)
	{
		ptr = extsys;
	}

	if (ret != NULL)
	{
		*ret = (ptr == NULL) ? IFACE_FAILED : IFACE_OK;
	}

	return ptr;
}
