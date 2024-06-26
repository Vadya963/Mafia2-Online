/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Shared Library
* File       : CSharedPlayerNatives.cpp
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#include "CString.h"

#include "BaseInc.h"
#include "CCore.h"

#include "CPlayerManager.h"
#ifdef _CLIENT
#	include	"CRemotePlayer.h"
#endif
#include "CNetworkPlayer.h"

#include "CEvents.h"
#include "CCommands.h"
#include "Scripting/CSquirrelCommon.h"

#include "CSharedPlayerNatives.h"

void CSharedPlayerNatives::Register( CScriptingManager * pScriptingManager )
{
	pScriptingManager->RegisterFunction( "getPlayers", GetPlayers, 0, NULL);
}

// getPlayers();
SQInteger CSharedPlayerNatives::GetPlayers(SQVM * pVM)
{
	SQInteger iCount = 0;

	sq_newtable(pVM);

	CPlayerManager *pPlayerManager = CCore::Instance()->GetPlayerManager();

	for (EntityId id = 0; id < MAX_PLAYERS; ++id)
	{
		if (!pPlayerManager->IsActive(id))
		{
			continue;
		}

		sq_pushinteger(pVM, id);
		sq_pushstring(pVM, pPlayerManager->Get(id)->GetNick(), -1);

		sq_createslot(pVM, -3);
		iCount++;
	}
	return 1;
}