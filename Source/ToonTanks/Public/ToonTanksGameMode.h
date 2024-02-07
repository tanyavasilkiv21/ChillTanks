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
	template<class ActorClass>
	int32 GetActorInLevelCount(ActorClass ClassOfActor);
	TSubclassOf<class APlayerPoint> GetPlayersPointClass();
	TSubclassOf<class ATower> GetTowersClass();
private:
	//variables
	class ATank* Player;
	class AToonTanksPlayerController* ToonTanksPlayerController;
	
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	TSubclassOf<class AHealWrench> HealWrenchClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Points")
	TSubclassOf<APlayerPoint> PlayerPointClass;

	UPROPERTY(EditDefaultsOnly, Category = "Towers")
	TSubclassOf<ATower> TurretTower;
	UPROPERTY(EditDefaultsOnly, Category = "Towers")
	TSubclassOf<ATower> Tower;
	
	float StartDelay = 3.f;
	UPROPERTY(EditAnywhere)
	float HealDelay = 10.f;
	TArray<FVector> LocationsOfWrenches = {{-133, -284, 20},
		{933, -847, 20}, {1647, -284, 20}, {700, -284, 20}};
	
	//functions
	void HandleGameStart();
	void TimerRespawnWrench();
};

