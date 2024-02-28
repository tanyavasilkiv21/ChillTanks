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
	if(CountPlayerPointsCurrent == 0)
	{
		GameOver(true);
		TArray<AActor*> TowerInTheWorld;
		UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowerInTheWorld);
		for(int32 i = 0; i < TowerInTheWorld.Num(); i++)
		{
			ATower* Temp = Cast<ATower>(TowerInTheWorld[i]);
			Temp->SetIsGamePlay(false);
		}
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		ToonTanksPlayerController->bShowMouseCursor = true;
		SetActorTickEnabled(false);
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	CountTowersStart = GetTowersInLevelCount();
	CountPlayerPointsStart = GetPlayersPointsInLevelCount();
	CountTowersCurrent = CountTowersStart;
	CountPlayerPointsCurrent = CountPlayerPointsStart;
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
		CountTowersCurrent--;
	}
	else if(ABreakingWall* DestroyedWall = Cast<ABreakingWall>(DeadActor))
	{
		DestroyedWall->HandleDistraction();
	}
}

void AToonTanksGameMode::SpawnWrenchInWorld()
{
	if(GetHealsInLevelCount() == 0)
	{
		GetWorld()->SpawnActor(HealWrenchClass,
		&LocationsOfWrenches[FMath::RandRange(0, LocationsOfWrenches.Num()-1)]);
	}
}

void AToonTanksGameMode::DecreasePlayersPoints()
{
	CountPlayerPointsCurrent--;
}

int32 AToonTanksGameMode::GetPlayerPointsStart() const
{
	return CountPlayerPointsStart;
}

int32 AToonTanksGameMode::GetPlayerPointsCurrent() const
{
	return CountPlayerPointsCurrent;
}

int32 AToonTanksGameMode::GetTowersStart() const
{
	return CountTowersStart;
}

int32 AToonTanksGameMode::GetTowersCurrent() const
{
	return CountTowersCurrent;
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

int32 AToonTanksGameMode::GetTowersInLevelCount()
{
	TArray<AActor*> ActorInTheWorld;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), ActorInTheWorld);
	return ActorInTheWorld.Num();
}

int32 AToonTanksGameMode::GetPlayersPointsInLevelCount()
{
	TArray<AActor*> ActorInTheWorld;
	UGameplayStatics::GetAllActorsOfClass(this, PlayerPointClass, ActorInTheWorld);
	return ActorInTheWorld.Num();
}

int32 AToonTanksGameMode::GetHealsInLevelCount()
{
	TArray<AActor*> ActorInTheWorld;
	UGameplayStatics::GetAllActorsOfClass(this, HealWrenchClass, ActorInTheWorld);
	return ActorInTheWorld.Num();
}


