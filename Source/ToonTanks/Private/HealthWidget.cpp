// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"

#include "HealthComponent.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void UHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

float UHealthWidget::CalculateHealthPercentage()
{
	if(Player)
	{
		PlayerHealthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
		if(PlayerHealthComponent)
		{
			return PlayerHealthComponent->GetHealth() / PlayerHealthComponent->GetMaxHealth();
		}
	}
	return 0.f;
}
