// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
public:
	virtual void Tick(float DeltaSeconds) override;

private:
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
	void SpawnWrenchInWorld();
	void DecreasePlayersPoints();

	int32 GetPlayerPointsStart() const;
	int32 GetPlayerPointsCurrent() const;
	int32 GetTowersStart() const;
	int32 GetTowersCurrent() const;
private:
	//variables
	class ATank* Player;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	int32 CountPlayerPointsStart;
	int32 CountTowersStart;
	
	int32 CountPlayerPointsCurrent;
	int32 CountTowersCurrent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	TSubclassOf<class AHealWrench> HealWrenchClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Points")
	TSubclassOf<class APlayerPoint> PlayerPointClass;
	
	float StartDelay = 3.f;
	UPROPERTY(EditAnywhere)
	float HealDelay = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	TArray<FVector> LocationsOfWrenches;
	
	//functions
	void HandleGameStart();
	void TimerRespawnWrench();

	int32 GetTowersInLevelCount();
	int32 GetPlayersPointsInLevelCount();
	int32 GetHealsInLevelCount();
};

