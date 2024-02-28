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

void ATower::SetIsGamePlay(bool Data)
{
	IsGamePlay = Data;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	
	GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATower::CheckFireCondition, FireRate, true);
	
}

void ATower::CheckFireCondition()
{
	if(InFireRange() && !(Tank->IsHidden()) && IsGamePlay)
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
			FVector Start = GetActorLocation();
			FVector End = Tank->GetActorLocation();
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this);
			
			if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
			{
				if(HitResult.GetActor() == Tank)
				{
					return true;
				}
			}		
		}
	}
	return false;
}
