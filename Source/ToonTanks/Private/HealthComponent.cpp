// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::DamageTaken(float Damage)
{
	if(Damage <= 0.f)
	{
		return;
	}
	Health -= Damage;
	if(Health <= 0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(GetOwner());
	}
}

void UHealthComponent::HealHealth(float Heal)
{
	if(Health == MaxHealth)
	{
		return;
	}
	if (Health + Heal == MaxHealth || Health + Heal <= MaxHealth)
	{
		Health += Heal;
	}
	else if (Health + Heal > MaxHealth)
	{
		auto TempDamage = MaxHealth - Health;
		Health += TempDamage;
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UHealthComponent::GetHealth() const 
{
	return Health;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

