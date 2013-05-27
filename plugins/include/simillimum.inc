/**
 * vim: set ts=4 :
 * =============================================================================
 * Simillimum (C)2013-2013 Simillimum Team.  All rights reserved.
 * =============================================================================
 *
 * This file is part of the Simillimum SDK.
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
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#if defined _simillimum_included
 #endinput
#endif
#define _simillimum_included


#include <sourcemod>



/**
 * Checks whether Simillimum is available.
 * Check the first native of Simillimum
 *
 * @return			True if simillimum is available, otherwise false.
 */
stock bool:IsSimillimumAvailable()
{
	return (GetFeatureStatus(FeatureType_Native, "GetHandleStatus") == FeatureStatus_Available)
}


/**
 * Returns the current status of a handle.
 *
 * @param hndl		Handle to get status for.
 * @return			HandleError item.
 */
native HandleError:GetHandleStatus(Handle:hndl);