// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GA/ABGA_Rotate.h"
#include "GameFramework/RotatingMovementComponent.h"

void UABGA_Rotate::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (AvatarActor)
	{
		URotatingMovementComponent* RotatingMovement = Cast<URotatingMovementComponent>(AvatarActor->GetComponentByClass(URotatingMovementComponent::StaticClass()));
		if (RotatingMovement)
		{
			RotatingMovement->Deactivate();
		}
	}
	
}

void UABGA_Rotate::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (AvatarActor)
	{
		URotatingMovementComponent* RotatingMovement = Cast<URotatingMovementComponent>(AvatarActor->GetComponentByClass(URotatingMovementComponent::StaticClass()));
		if (RotatingMovement)
		{
			RotatingMovement->Activate(true);
		}
	}
	
}