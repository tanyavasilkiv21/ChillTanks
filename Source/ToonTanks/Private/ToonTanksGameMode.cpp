// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "BreakingWall.h"
#include "HealWrench.h"
#include "PlayerPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Engine/EngineTypes.h"

void AToonTanksGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(GetActorInLevelCount(PlayerPointClass) == 0)
	{
		GameOver(true);
		ToonTanksPlayerController->SetPlayerEnabledState(false);
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
	TimerRespawnWrench();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor) 
{
	if(DeadActor == Player)
	{
		Player->HandleDistraction();
		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDistraction();
	}
	else if(ABreakingWall* DestroyedWall = Cast<ABreakingWall>(DeadActor))
	{
		DestroyedWall->HandleDistraction();
	}
}

void AToonTanksGameMode::SpawnWrenchInWorld()
{
	if(GetActorInLevelCount(HealWrenchClass) == 0)
	{
		GetWorld()->SpawnActor(HealWrenchClass,
		&LocationsOfWrenches[FMath::RandRange(0, LocationsOfWrenches.Num()-1)]);
	}
}

TSubclassOf<APlayerPoint> AToonTanksGameMode::GetPlayersPointClass() 
{
	return PlayerPointClass;
}

TSubclassOf<ATower> AToonTanksGameMode::GetTowersClass() 
{
	return ATower::StaticClass();
}


void AToonTanksGameMode::HandleGameStart()
{
	Player = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	StartGame();
	
	if(ToonTanksPlayerController)
	{
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate =  FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false);
	}
}

void AToonTanksGameMode::TimerRespawnWrench()
{
	FTimerHandle WrenchRespawnTimer;
	GetWorldTimerManager().SetTimer(WrenchRespawnTimer, this,
		&AToonTanksGameMode::SpawnWrenchInWorld, HealDelay, true, -1);
}

template <class ActorClass>
int32 AToonTanksGameMode::GetActorInLevelCount(ActorClass ClassOfActor)
{
	TArray<AActor*> ActorInTheWorld;
	UGameplayStatics::GetAllActorsOfClass(this, ClassOfActor, ActorInTheWorld);
	return ActorInTheWorld.Num();
}

