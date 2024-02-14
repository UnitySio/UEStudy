// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Character/ABGA_AttackHitCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Character/ABAT_Trace.h"
#include "AbilitySystem/Character/ABTA_Trace.h"

UABGA_AttackHitCheck::UABGA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UABAT_Trace* TraceTask = UABAT_Trace::CreateTask(this, AABTA_Trace::StaticClass());
	TraceTask->OnComplete.AddDynamic(this, &UABGA_AttackHitCheck::OnTraceResultCallback);
	TraceTask->ReadyForActivation();
	
}

void UABGA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
	}
	
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
