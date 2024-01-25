// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	//GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
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
	UE_LOG(LogTemp, Warning, TEXT("Health of %s: %f"), *GetOwner()->GetName(), Health);
}

void UHealthComponent::HealHealth(float Heal)
{
	if(Health == MaxHealth)
	{
		return;
	}
	else if (Health + Heal == MaxHealth || Health + Heal <= MaxHealth)
	{
		Health += Heal;
	}
	else if (Health + Heal > MaxHealth)
	{
		auto TempDamage = MaxHealth - Health;
		Health += TempDamage;
	}
	UE_LOG(LogTemp, Warning, TEXT("Healing Health of %s: %f"), *GetOwner()->GetName(), Health);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

