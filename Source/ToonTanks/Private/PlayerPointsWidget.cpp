// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPointsWidget.h"

#include "ToonTanksGameMode.h"

void UPlayerPointsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<AToonTanksGameMode>(GetWorld()->GetAuthGameMode());
	PlayerPointsInStart = CalculateCountPlayerPoints();
}

int32 UPlayerPointsWidget::GetPlayerPointsInStart()
{
	return PlayerPointsInStart;
}

int32 UPlayerPointsWidget::CalculateCountPlayerPoints()
{
	return GameMode->GetActorInLevelCount(GameMode->GetPlayersPointClass());
}

int32 UPlayerPointsWidget::CalculateCollectedCountPlayerPoints()
{
	return (PlayerPointsInStart - CalculateCountPlayerPoints());
}

