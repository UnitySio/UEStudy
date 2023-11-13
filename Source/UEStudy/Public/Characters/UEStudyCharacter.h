// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
#include "GameFramework/Character.h"
#include "UEStudyCharacter.generated.h"

class AItem;
class AWeapon;

UCLASS()
class UESTUDY_API AUEStudyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUEStudyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE void SetOverlappingItem(AItem* item) { OverlappingItem = item; }

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Zoom(float Value);
	void EKeyPressed();
	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

private:
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponActor;
	
	UPROPERTY()
	AWeapon* SpawnedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* AttackMontage;

};
