// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Character/ABAT_Trace.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Character/ABTA_Trace.h"

UABAT_Trace::UABAT_Trace()
{
}

UABAT_Trace* UABAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AABTA_Trace> TargetActorClass)
{
	UABAT_Trace* NewTask = NewAbilityTask<UABAT_Trace>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void UABAT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitalizeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void UABAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}
	
	Super::OnDestroy(bInOwnerFinished);
}

void UABAT_Trace::SpawnAndInitalizeTargetActor()
{
	SpawnedTargetActor = Cast<AABTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UABAT_Trace::OnTargetDataReadyCallback);
	}
}

void UABAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		SpawnedTargetActor->ConfirmTargeting();
	}
}

void UABAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}
