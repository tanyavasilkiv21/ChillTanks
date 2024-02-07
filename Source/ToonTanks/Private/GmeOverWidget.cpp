// Fill out your copyright notice in the Description page of Project Settings.


#include "GmeOverWidget.h"

#include "PlayerPointsWidget.h"
#include "ToonTanksGameMode.h"

void UGmeOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<AToonTanksGameMode>(GetWorld()->GetAuthGameMode());
	TowersInStart = CalculateCountTowers();
}

int32 UGmeOverWidget::GetTowersInStart()
{
	return TowersInStart;
}

int32 UGmeOverWidget::CalculateCountTowers()
{
	return GameMode->GetActorInLevelCount(GameMode->GetTowersClass());
	
}

int32 UGmeOverWidget::CalculateCollectedCountTowers()
{
	return (TowersInStart - CalculateCountTowers());
}
