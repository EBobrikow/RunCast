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

//void UMessageHandler::AddCallback(FOnMessageRecieved& callback)
//{
//	OnMessageRecievedCallback = callback;
//	OnMessageRecievedCallback.AddDynamic(this, &UMessageHandler::OnURecieved);
//}

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
	//{"Id":1,"serverName":"Yahoo","port":1001,"host":"ws://127.0.0.1","matchStatus":0}
	FServerInfo servInfo = FServerInfo();
	
	for (auto val : JsonObj->Values)
	{
		if (val.Value->IsNull())
		{
			continue;
		}
		if (parseAsNumber(val, JSVal::ServerInfo::Id, servInfo.Id)) {}
		else if (parseAsString(val, JSVal::ServerInfo::ServerName, servInfo.ServerName)) {}
		else if (parseAsNumber(val, JSVal::ServerInfo::Port, servInfo.Port)) {}
		else if (parseAsString(val, JSVal::ServerInfo::Host, servInfo.host)) {}
		else if (parseAsNumber(val, JSVal::ServerInfo::MatchStatus, servInfo.MatchStatus)) {}
	}
	serverInfo = servInfo;
}


void UServersListHandler::ParseJsonObject(TSharedPtr<FJsonObject> JsonObj)
{
	// [{"Id":1,"serverName":"Yahoo","port":1001,"host":"127.0.0.1","matchStatus":0},{"Id":2,"serverName":"Yahoo","port":1002,"host":"127.0.0.1","matchStatus":0}]

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
				for (auto serverInfo : inst->Values)
				{
					if (val.Value->IsNull())
					{
						continue;
					}
					if (parseAsNumber(serverInfo, JSVal::ServerInfo::Id, servInfoLoc.Id)) {}
					else if (parseAsString(serverInfo, JSVal::ServerInfo::ServerName, servInfoLoc.ServerName)) {}
					else if (parseAsNumber(serverInfo, JSVal::ServerInfo::Port, servInfoLoc.Port)) {}
					else if (parseAsString(serverInfo, JSVal::ServerInfo::Host, servInfoLoc.host)) {}
					else if (parseAsNumber(serverInfo, JSVal::ServerInfo::MatchStatus, servInfoLoc.MatchStatus)) {}
				}

				serversInfoList.Add(servInfoLoc);
			}
		}
	}

	/*for (auto file : val.Value->AsArray())
	{
		TSharedPtr<FJsonObject> inst = file->AsObject();
		for (auto tmpfile : inst->Values)
		{
			if (parseAsString(tmpfile, JSVal::Course::filename, coursefile._filename)) {
			}*/
}

void UServerInfoByPortHandler::ParseJsonObject(TSharedPtr<FJsonObject> JsonObj)
{
}
