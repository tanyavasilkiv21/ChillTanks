// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPointsWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UPlayerPointsWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	//variables
	class AToonTanksGameMode* GameMode;
	int32 PlayerPointsInStart;
	//functions
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintPure)
	int32 GetPlayerPointsInStart();
	int32 CalculateCountPlayerPoints();
	UFUNCTION(BlueprintPure)
	int32 CalculateCollectedCountPlayerPoints();
	
};
