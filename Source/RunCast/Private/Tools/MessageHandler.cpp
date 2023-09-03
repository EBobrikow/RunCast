// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/MessageHandler.h"

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

}
