// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ULZAsyncAction_RequestHttpMessage.generated.h"

// Event that will be the 'Completed' exec wire in the blueprint node along with all parameters as output pins.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHttpRequestCompleted, const FString&, ResponseString, bool, bSuccess);

UCLASS() // Change the _API to match your project
class HANDSTRAINSAMPLE_API ULZAsyncAction_RequestHttpMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

public:

	/** Execute the actual load */
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (Category = "HTTP", WorldContext = "WorldContextObject"))
	static ULZAsyncAction_RequestHttpMessage* AsyncRequestHTTP(UObject* WorldContextObject, FString URL, int FingerID, int Strength, int Mode = 0, int Duration = 0, int Round = 0);

	UPROPERTY(BlueprintAssignable)
	FOnHttpRequestCompleted Completed;

	/* URL to send GET request to */
	FString URL;
	int FingerID;
	int Strength;
	int Mode = 0;
	int Duration = 0;
	int Round = 0;
};