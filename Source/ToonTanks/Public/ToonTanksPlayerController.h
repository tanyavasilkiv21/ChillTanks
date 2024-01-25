// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
protected:
	virtual void BeginPlay() override;

private:
	GENERATED_BODY()

	bool bPlayerEnable = false;
public:
	void SetPlayerEnabledState(bool bPlayerEnabledData);
	bool IsEnable();
	
};
