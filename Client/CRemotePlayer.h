/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Client
* File       : CRemotePlayer.h
* Developers : AaronLad <aaron@m2-multiplayer.com>
*
***************************************************************/

#pragma once

#include "CNetworkPlayer.h"
#include "CSync.h"
#include "Math/CVector3.h"

class CRemotePlayer : public CNetworkPlayer
{

private:

	OnFootSync						m_onFootSync;
	OnFootSync						m_pendingOnFootSync;
	bool							m_bHasPendingOnFootSync;
	unsigned long					m_ulLastOnFootSyncProcessTime;

	void							ProcessOnFootSync			( const OnFootSync &onFootSync );
	void							ProcessPendingOnFootSync	( void );

public:

	CRemotePlayer( void );
	~CRemotePlayer( void );

	void							Pulse( void );

	void							StoreOnFootSync( const OnFootSync &onFootSync );
	void							StoreInVehicleSync( EntityId vehicleId, const InVehicleSync &inVehicleSync );
	void							StorePassengerSync( const InPassengerSync &passengerSync );

	bool							IsPositionOutOfRange ( CVector3 vecPos );

};
