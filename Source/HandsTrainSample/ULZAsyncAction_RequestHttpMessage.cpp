#include "ULZAsyncAction_RequestHttpMessage.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void ULZAsyncAction_RequestHttpMessage::Activate()
{
	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(URL);
	const FString Json = FString::Printf(TEXT("{\"gpio\": %d, \"intensity\": %d, \"time\": %d, \"mode\": %d, \"duration\": %d, \"round\": %d }"), FingerID, Strength, 9999, Mode, Duration, Round);
	
	UE_LOG(LogLevel, Display, TEXT("Request: %s"), *Json);
	HttpRequest->SetContentAsString(Json);

	// Setup Async response
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			FString ResponseString = "";
			if (bSuccess)
			{
				ResponseString = Response->GetContentAsString();
			}

			UE_LOG(LogLevel, Display, TEXT("Response: %s"), *ResponseString);
			this->HandleRequestCompleted(ResponseString, bSuccess);
		});

	// Handle actual request
	HttpRequest->ProcessRequest();
}


void ULZAsyncAction_RequestHttpMessage::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	Completed.Broadcast(ResponseString, bSuccess);
}


ULZAsyncAction_RequestHttpMessage* ULZAsyncAction_RequestHttpMessage::AsyncRequestHTTP(UObject* WorldContextObject, FString URL, const int FingerID, const int Strength, const int Mode, const int Duration, const int Round)
{
	// Create Action Instance for Blueprint System
	ULZAsyncAction_RequestHttpMessage* Action = NewObject<ULZAsyncAction_RequestHttpMessage>();
	Action->URL = URL;
	Action->FingerID = FingerID;
	Action->Strength = Strength;
	Action->Mode = Mode;
	Action->Duration = Duration;
	Action->Round = Round;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}