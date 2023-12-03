// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/Server/MessageHandler.h"

void UMessageHandler::OnURecieved(FString message)
{
	OnRecieved(message);
}

void UMessageHandler::OnRecieved(FString message)
{
	// parse message
	FString msg = message;
	TSharedPtr<FJsonObject> JsonObject;
	if (msg[0] != '{')
	{
		msg = FString::Printf(TEXT("{\"object\":%s}"), *msg);

	}
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(msg);
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		ParseJsonObject(JsonObject);
	}

	RequestAction();
}

const FString& UMessageHandler::GetRequestMessage() const
{
	return requestMessage;
}

void UMessageHandler::SetRequestMessage(const FString& message)
{
	requestMessage = message;
	
}

void UMessageHandler::RequestAction()
{
	if (OnRequestFinished.IsBound())
	{
		OnRequestFinished.Broadcast(this);
	}
}

FServerInfo UMessageHandler::ParseServerInfoObject(TSharedPtr<FJsonObject> JsonObj)
{
	FServerInfo tmp = FServerInfo();

	for (auto val : JsonObj->Values)
	{
		if (val.Value->IsNull())
		{
			continue;
		}
		if (parseAsNumber(val, JSVal::ServerInfo::Id, tmp.Id)) {}
		else if (parseAsString(val, JSVal::ServerInfo::ServerName, tmp.ServerName)) {}
		else if (parseAsNumber(val, JSVal::ServerInfo::Port, tmp.Port)) {}
		else if (parseAsString(val, JSVal::ServerInfo::Host, tmp.host)) {}
		else if (parseAsNumber(val, JSVal::ServerInfo::MatchStatus, tmp.MatchStatus)) {}
		else if (parseAsString(val, JSVal::ServerInfo::MatchType, tmp.MatchType)) {}
		else if (parseAsString(val, JSVal::ServerInfo::MapName, tmp.MapName)) {}
		else if (parseAsNumber(val, JSVal::ServerInfo::CurrPlayers, tmp.CurrPlayers)) {}
		else if (parseAsNumber(val, JSVal::ServerInfo::MaxPlayers, tmp.MaxPlayers)) {}
	}

	return tmp;
}


void UMessageHandler::ParseJsonObject(TSharedPtr<FJsonObject> JsonObj)
{

}

bool UMessageHandler::parseAsString(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, FString& value)
{
	if (val.Key == fieldName && !val.Value->IsNull()) {
		value = val.Value->AsString();
		return true;
	}
	return false;
}

bool UMessageHandler::parseAsNumber(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, int32& value)
{
	if (val.Key == fieldName && !val.Value->IsNull()) {
		value = val.Value->AsNumber();
		return true;
	}
	return false;
}

bool UMessageHandler::parseAsNumber(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, double& value)
{
	if (val.Key == fieldName && !val.Value->IsNull()) {
		value = val.Value->AsNumber();
		return true;
	}
	return false;
}

bool UMessageHandler::parseAsBool(TPair<FString, TSharedPtr<FJsonValue>> const& val, const FString& fieldName, bool& value)
{
	if (val.Key == fieldName && !val.Value->IsNull()) {
		value = val.Value->AsBool();
		return true;
	}
	return false;
}

void URequestNewServerHandler::ParseJsonObject(TSharedPtr<FJsonObject> JsonObj)
{
	serverInfo = ParseServerInfoObject(JsonObj);//FServerInfo();
}


void UServersListHandler::ParseJsonObject(TSharedPtr<FJsonObject> JsonObj)
{
	
	for (auto val : JsonObj->Values)
	{
		if (val.Value->IsNull())
		{
			continue;
		}
		if (val.Key == "object")
		{
			for (auto serverInfoObj : val.Value->AsArray())
			{
				FServerInfo servInfoLoc = FServerInfo();
				TSharedPtr<FJsonObject> inst = serverInfoObj->AsObject();
				servInfoLoc = ParseServerInfoObject(inst);
				

				serversInfoList.Add(servInfoLoc);
			}
		}
	}

}

void UServerInfoByPortHandler::ParseJsonObject(TSharedPtr<FJsonObject> JsonObj)
{
	//{"Id":1,"serverName":"Yahoo","port":1001,"host":"127.0.0.1","matchStatus":0,"matchType":null,"mapName":null,"currentPlayers":0,"maxPlayers":0}

	currentServersInfo = ParseServerInfoObject(JsonObj);//FServerInfo();

	
	
}

void UHeartBeatHandler::ParseJsonObject(TSharedPtr<FJsonObject> JsonObj)
{
	heartBeatServersInfo = ParseServerInfoObject(JsonObj);//FServerInfo();
}
