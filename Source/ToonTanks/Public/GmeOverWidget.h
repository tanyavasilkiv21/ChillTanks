// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPointsWidget.h"
#include "GmeOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UGmeOverWidget : public UPlayerPointsWidget
{
	GENERATED_BODY()
protected:
	//variables
	int32 TowersInStart;
	//functions
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	int32 GetTowersInStart();
	int32 CalculateCountTowers();
	UFUNCTION(BlueprintPure)
	int32 CalculateCollectedCountTowers();
};
