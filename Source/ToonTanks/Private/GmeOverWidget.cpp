// Fill out your copyright notice in the Description page of Project Settings.


#include "GmeOverWidget.h"

#include "PlayerPointsWidget.h"
#include "ToonTanksGameMode.h"

void UGmeOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<AToonTanksGameMode>(GetWorld()->GetAuthGameMode());
}

int32 UGmeOverWidget::GetTowersInStart()
{
	return GameMode->GetTowersStart();
}

int32 UGmeOverWidget::GetTowersCurrent()
{
	return GameMode->GetTowersStart() - GameMode->GetTowersCurrent();
}
