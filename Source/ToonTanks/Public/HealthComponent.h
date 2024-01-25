// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	
protected:
	virtual void BeginPlay() override;
	
private:
	//variables
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float Health = 0.f;

	class UHitBoxComponent* HitBoxComponent;
	class AToonTanksGameMode* ToonTanksGameMode;
	
public:
	//functions
	UFUNCTION()
	void DamageTaken(float Damage);
	void HealHealth(float Heal);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
