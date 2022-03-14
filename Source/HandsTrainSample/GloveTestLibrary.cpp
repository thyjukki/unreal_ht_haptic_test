// Fill out your copyright notice in the Description page of Project Settings.


#include "GloveTestLibrary.h"

FString UGloveTestLibrary::GetGloveAddress(const FString HandType)
{
	UE_LOG(LogLevel, Display, TEXT("HandType: %s"), *HandType);
	if (HandType == "Left")
	{
		return "http://192.168.2.112/api/events";
	}
	if (HandType == "Right")
	{
		return "http://192.168.2.195/api/events";
	}

	return "NULL";
}
