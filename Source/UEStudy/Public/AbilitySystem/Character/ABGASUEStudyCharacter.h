// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/UEStudyCharacter.h"
#include "AbilitySystemInterface.h"
#include "ABGASUEStudyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UESTUDY_API AABGASUEStudyCharacter : public AUEStudyCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AABGASUEStudyCharacter();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// 폰이 빙의가 되었을 때 호출
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void SetupGASInputComponent();
	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;
	
};
