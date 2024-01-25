// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"


UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDistraction() override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	//variables
	UPROPERTY(EditAnywhere, Category= "Distance")
	float FireRange = 1000.f;
	class ATank *Tank;
	FTimerHandle FireRateTimeHandle;
	float FireRate = 2.f;
	
	//functions
	void CheckFireCondition();
	bool InFireRange();
};
