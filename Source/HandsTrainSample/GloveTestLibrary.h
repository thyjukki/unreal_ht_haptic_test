// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GloveTestLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HANDSTRAINSAMPLE_API UGloveTestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable,Category="GloveFunctions")
		static FString GetGloveAddress(FString HandType);
};
