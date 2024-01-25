// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "HitBoxComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHitBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	UHitBoxComponent();

private:
	UPROPERTY(EditAnywhere, Category= "Damage")
	float PercentDamageReduced = 10.f;

	class UHealthComponent* HealthComponent;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void DamageReduced(float& Damage);
	void DamageHealed(float Heal);
};
