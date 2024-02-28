// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPointsWidget.h"
#include "ToonTanksGameMode.h"

void UPlayerPointsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<AToonTanksGameMode>(GetWorld()->GetAuthGameMode());
}

int32 UPlayerPointsWidget::GetPlayerPointsInStart()
{
	return GameMode->GetPlayerPointsStart();
}

int32 UPlayerPointsWidget::GetPlayerPointsCurrent()
{
	return GameMode->GetPlayerPointsStart() - GameMode->GetPlayerPointsCurrent();
}
