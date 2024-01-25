// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//GetPawn()->DisableInput(this);
	bShowMouseCursor = false;
}

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabledData)
{
	if(bPlayerEnabledData)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabledData;
	bPlayerEnable = bPlayerEnabledData;
}

bool AToonTanksPlayerController::IsEnable()
{
	return bPlayerEnable;
}
