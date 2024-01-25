// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	//events
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	
public:
	void ActorDied(AActor* DeadActor);
	
private:
	//variables
	class ATank * Player;
	class AToonTanksPlayerController * ToonTanksPlayerController;
	float StartDelay = 3.f;
	
	//functions
	void HandleGameStart();
	int32 GetTargetTowerCount();
};
