// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(InFireRange())
	{
		RotatePawn(Tank->GetActorLocation());
	}	
}

void ATower::HandleDistraction()
{
	Super::HandleDistraction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if(InFireRange() && !(Tank->IsHidden()))
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(Distance <=  FireRange)
		{
			return true;
		}
	}
	return false;
}
