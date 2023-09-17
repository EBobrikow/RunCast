// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/Globals.h"

FServerInfo::FServerInfo()
	: FServerInfo(-1, TEXT(""), 0 , TEXT(""), 0, TEXT(""), TEXT(""), 0, 0)
{
}

FServerInfo::FServerInfo(int32 _id, const FString& _serverName, int32 _port, const FString& _host,
						 int32 _matchStatus, const FString& _matchType, const FString& _mapName, int32 _currPlayers, int32 maxPlayers)
	: Id(_id)
	, ServerName(_serverName)
	, Port(_port)
	, host(_host)
	, MatchStatus(_matchStatus)
	, MatchType(_matchType)
	, MapName(_mapName)
	, CurrPlayers(_currPlayers)
	, MaxPlayers(maxPlayers)
{
}

FPlayerData::FPlayerData()
	: FPlayerData(TEXT(""), ELobbyPlayerAuthority::None, ELobbyPlayerReady::None)
{
}

FPlayerData::FPlayerData(FString name, ELobbyPlayerAuthority authority, ELobbyPlayerReady isReady)
	: PlayerName(name)
	, PlayerAuthority(authority)
	, PlayerReady(isReady)
{
}
