// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/Globals.h"

FServerInfo::FServerInfo()
	: FServerInfo(0, TEXT(""), 0 , TEXT(""), 0)
{
}

FServerInfo::FServerInfo(int32 _id, const FString& _serverName, int32 _port, const FString& _host, int32 _matchStatus)
	: Id(_id)
	, ServerName(_serverName)
	, Port(_port)
	, host(_host)
	, MatchStatus(_matchStatus)
{
}
