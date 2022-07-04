/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Shared Library
* File       : CSharedPlayerNatives.h
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#pragma once

class CScriptingManager;

class CSharedPlayerNatives
{

private:

	static	SQInteger		GetPlayers( SQVM * pVM );

public:

	static	void			Register( CScriptingManager * pScriptingManager );

};