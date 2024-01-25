// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBoxComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UHitBoxComponent::UHitBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHitBoxComponent::BeginPlay()
{
	Super::BeginPlay();
	
	auto HealthRef = GetOwner()->GetComponentByClass(UHealthComponent::StaticClass());
	if(HealthRef)
	{
		HealthComponent = Cast<UHealthComponent>(HealthRef);
	}
}


// Called every frame
void UHitBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHitBoxComponent::DamageReduced(float& Damage)
{
	Damage -= (Damage * PercentDamageReduced) / 100;
	HealthComponent->DamageTaken(Damage);
}

void UHitBoxComponent::DamageHealed(float Heal)
{
	HealthComponent->HealHealth(Heal);
}

