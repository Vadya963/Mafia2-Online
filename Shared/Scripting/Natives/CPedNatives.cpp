/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Shared Library
* File       : CPedNatives.cpp
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#include "Scripting/CScriptingManager.h"

#include "CPedNatives.h"
#include "Math/CMaths.h"
#include "Scripting/CSquirrelCommon.h"

#include "CLogFile.h"

#include "BaseInc.h"
#include "CCore.h"

#include "CPedManager.h"

#include "CEvents.h"
#include "CCommands.h"

void CPedNatives::Register( CScriptingManager * pScriptingManager )
{
	pScriptingManager->RegisterFunction( "createPed", CreatePed, 7, "iffffff" );
	pScriptingManager->RegisterFunction( "destroyPed", DestroyPed, 1, "i" );
	pScriptingManager->RegisterFunction( "setPedName", SetPedName, 2, "is" );
	pScriptingManager->RegisterFunction( "getPedName", GetPedName, 1, "i" );
	pScriptingManager->RegisterFunction( "showPedName", ShowPedName, 2, "ib" );
	pScriptingManager->RegisterFunction( "setPedModel", SetPedModel, 2, "ii" );
	pScriptingManager->RegisterFunction( "getPedModel", GetPedModel, 1, "i" );
	pScriptingManager->RegisterFunction( "getPedPosition", GetPedPosition, 1, "i" );
	pScriptingManager->RegisterFunction( "setPedPosition", SetPedPosition, 4, "ifff" );
	pScriptingManager->RegisterFunction( "getPedRotation", GetPedRotation, 1, "i" );
	pScriptingManager->RegisterFunction( "setPedRotation", SetPedRotation, 4, "ifff" );
	pScriptingManager->RegisterFunction( "pedMoveTo", PedMove, 5, "ifffi" );
	pScriptingManager->RegisterFunction( "pedShootTo", PedShoot, 4, "ifff" );
	pScriptingManager->RegisterFunction( "pedAimTo", PedAim, 4, "ifff" );
	pScriptingManager->RegisterFunction( "givePedWeapon", GiveWeapon, 3, "iii" );
	pScriptingManager->RegisterFunction( "setPedWeapon", SetWeapon, 2, "ii" );

	pScriptingManager->RegisterConstant( "MOVE_WALK", M2Enums::eMoveType::E_WALK );
	pScriptingManager->RegisterConstant( "MOVE_JOG", M2Enums::eMoveType::E_JOG );
	pScriptingManager->RegisterConstant( "MOVE_SPRINT", M2Enums::eMoveType::E_SPRINT );
}

SQInteger CPedNatives::GiveWeapon(SQVM * pVM)
{
	SQInteger pedId;
	SQInteger weapon;
	SQInteger ammo;

	sq_getinteger(pVM, -3, &pedId);
	sq_getinteger(pVM, -2, &weapon);
	sq_getinteger(pVM, -1, &ammo);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->GiveWeapon(weapon, ammo);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::SetWeapon(SQVM * pVM)
{
	SQInteger pedId;
	SQInteger weapon;

	sq_getinteger(pVM, -2, &pedId);
	sq_getinteger(pVM, -1, &weapon);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->SetSelectedWeapon(weapon, true);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::PedMove(SQVM * pVM)
{
	CVector3 pos;
	SQInteger pedId;
	SQInteger mode;

	sq_getinteger(pVM, -5, &pedId);
	sq_getfloat(pVM, -4, &pos.fX);
	sq_getfloat(pVM, -3, &pos.fY);
	sq_getfloat(pVM, -2, &pos.fZ);
	sq_getinteger(pVM, -1, &mode);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->MoveVec(pos, static_cast<M2Enums::eMoveType>(mode), pos);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::PedShoot(SQVM * pVM)
{
	CVector3 pos;
	SQInteger pedId;

	sq_getinteger(pVM, -4, &pedId);
	sq_getfloat(pVM, -3, &pos.fX);
	sq_getfloat(pVM, -2, &pos.fY);
	sq_getfloat(pVM, -1, &pos.fZ);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->ShootAt(pos);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::PedAim(SQVM * pVM)
{
	CVector3 pos;
	SQInteger pedId;

	sq_getinteger(pVM, -4, &pedId);
	sq_getfloat(pVM, -3, &pos.fX);
	sq_getfloat(pVM, -2, &pos.fY);
	sq_getfloat(pVM, -1, &pos.fZ);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->AimAt(pos);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::CreatePed( SQVM * pVM )
{
	SQInteger iModelIndex;
	CVector3 vecPosition;
	CVector3 vecRotation;

	sq_getinteger( pVM, -7, &iModelIndex );

	sq_getfloat( pVM, -6, &vecPosition.fX );
	sq_getfloat( pVM, -5, &vecPosition.fY );
	sq_getfloat( pVM, -4, &vecPosition.fZ );

	sq_getfloat( pVM, -3, &vecRotation.fX );
	sq_getfloat( pVM, -2, &vecRotation.fY );
	sq_getfloat( pVM, -1, &vecRotation.fZ );

	DEBUG_LOG ( "Model: %d, Pos: %f, %f, %f, Rot: %f, %f, %f", iModelIndex, vecPosition.fX, vecPosition.fY, vecPosition.fZ, vecRotation.fX, vecRotation.fY, vecRotation.fZ );

	// Add the ped to the manager
	sq_pushinteger( pVM, CCore::Instance()->GetPedManager()->Add( iModelIndex, vecPosition, vecRotation ) );
	return 1;
}

SQInteger CPedNatives::DestroyPed( SQVM * pVM )
{
	SQInteger pedId;
	sq_getinteger( pVM, -1, &pedId );

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		// Delete the ped from the manager
		sq_pushbool(pVM, CCore::Instance()->GetPedManager()->Delete(pedId));
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::SetPedName(SQVM * pVM)
{
	SQInteger pedId;
	const SQChar *pedName;

	sq_getinteger(pVM, -2, &pedId);
	sq_getstring(pVM, -1, &pedName);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		// Change nick
		CCore::Instance()->GetPedManager()->Get(pedId)->SetNick(pedName);

		// Push the return
		sq_pushbool(pVM, true);
		return (1);
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::GetPedName(SQVM * pVM)
{
	SQInteger pedId;

	sq_getinteger(pVM, -1, &pedId);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		// Get the nick
		String nick = CCore::Instance()->GetPedManager()->Get(pedId)->GetNick();

		// Push the return
		sq_pushstring(pVM, nick.Get(), nick.GetLength());
		return (1);
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::ShowPedName(SQVM *pVM)
{
	SQInteger	pedId;
	SQBool		bShow;

	sq_getinteger(pVM, -2, &pedId);
	sq_getbool(pVM, -1, &bShow);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		// Change nick state
		CCore::Instance()->GetPedManager()->Get(pedId)->ShowNick(bShow);

		// Return
		sq_pushbool(pVM, true);
		return (1);
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::GetPedModel(SQVM *pVM)
{
	SQInteger	pedId;

	sq_getinteger(pVM, -1, &pedId);
	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		sq_pushinteger(pVM, CCore::Instance()->GetPedManager()->Get(pedId)->GetModel());
		return (1);
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::SetPedModel(SQVM *pVM)
{
	SQInteger	pedId;
	SQInteger	pedModel;

	sq_getinteger(pVM, -2, &pedId);
	sq_getinteger(pVM, -1, &pedModel);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CCore::Instance()->GetPedManager()->Get(pedId)->SetModel(pedModel);

		sq_pushbool(pVM, true);
		return (1);
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::GetPedPosition(SQVM *pVM)
{
	SQInteger	pedId;

	sq_getinteger(pVM, -1, &pedId);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CVector3 pos;

		// Get the position
		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->GetPosition(&pos);

		// Create array
		sq_newarray(pVM, 0);

		sq_pushfloat(pVM, pos.fX);
		sq_arrayappend(pVM, -2);

		sq_pushfloat(pVM, pos.fY);
		sq_arrayappend(pVM, -2);

		sq_pushfloat(pVM, pos.fZ);
		sq_arrayappend(pVM, -2);

		// Return
		sq_push(pVM, -1);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::SetPedPosition( SQVM * pVM )
{
	SQInteger	pedId;

	sq_getinteger(pVM, -4, &pedId);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CVector3 vecPosition;
		sq_getfloat( pVM, -3, &vecPosition.fX );
		sq_getfloat( pVM, -2, &vecPosition.fY );
		sq_getfloat( pVM, -1, &vecPosition.fZ );

		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->SetPosition(vecPosition);

		sq_pushbool(pVM, true);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::GetPedRotation(SQVM *pVM)
{
	SQInteger	pedId;

	sq_getinteger(pVM, -1, &pedId);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		Quaternion rot;
		CVector3 vecRotation;

		// Get the position
		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->GetRotation(&rot);

		vecRotation = rot.toEularAngles();

		vecRotation.FromRadians();

		// Create array
		sq_newarray(pVM, 0);

		sq_pushfloat(pVM, vecRotation.fX);
		sq_arrayappend(pVM, -2);

		sq_pushfloat(pVM, vecRotation.fY);
		sq_arrayappend(pVM, -2);

		sq_pushfloat(pVM, vecRotation.fZ);
		sq_arrayappend(pVM, -2);

		// Return
		sq_push(pVM, -1);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}

SQInteger CPedNatives::SetPedRotation( SQVM * pVM )
{
	SQInteger	pedId;

	sq_getinteger(pVM, -4, &pedId);

	if (CCore::Instance()->GetPedManager()->IsActive(pedId) && CCore::Instance()->GetPedManager()->Get(pedId) != NULL)
	{
		CVector3 vecRotation;

		sq_getfloat( pVM, -3, &vecRotation.fX );
		sq_getfloat( pVM, -2, &vecRotation.fY );
		sq_getfloat( pVM, -1, &vecRotation.fZ );

		vecRotation.ToRadians();

		CCore::Instance()->GetPedManager()->Get(pedId)->GetPed()->SetRotation(Quaternion(vecRotation));

		sq_pushbool(pVM, true);
		return 1;
	}
	sq_pushbool(pVM, false);
	return 1;
}