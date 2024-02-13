// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Character/ABGA_Jump.h"

#include "AbilitySystem/Character/ABAT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

UABGA_Jump::UABGA_Jump()
{
	// 상태 보존을 위해 액터 별로 인스턴스를 생성
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UABGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
                                    FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (bResult == false) return false;

	const ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	return (Character && Character->CanJump());
}

void UABGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// UABAT_JumpAndWaitForLanding* JumpAndWaitingForLandingTask = UABAT_JumpAndWaitForLanding::CreateTask(this);
	// JumpAndWaitingForLandingTask->OnComplete.AddDynamic(this, &UABGA_Jump::OnLandedCallback);
	// JumpAndWaitingForLandingTask->ReadyForActivation();
}

void UABGA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	Character->StopJumping();
}

void UABGA_Jump::OnLandedCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
