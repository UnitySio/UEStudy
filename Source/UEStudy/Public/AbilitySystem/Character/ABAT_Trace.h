// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ABAT_Trace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * 
 */
UCLASS()
class UESTUDY_API UABAT_Trace : public UAbilityTask
{
	GENERATED_BODY()

public:
	UABAT_Trace();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitForTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UABAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AABTA_Trace> TargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	void SpawnAndInitalizeTargetActor();
	void FinalizeTargetActor();

	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;

protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);

	UPROPERTY()
	TSubclassOf<class AABTA_Trace> TargetActorClass;

	TObjectPtr<class AABTA_Trace> SpawnedTargetActor;
	
};
