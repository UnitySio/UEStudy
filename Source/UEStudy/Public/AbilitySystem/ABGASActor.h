// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "ABGASActor.generated.h"

UCLASS()
class UESTUDY_API AABGASActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AABGASActor();
	
	virtual void Tick(float DeltaTime) override;
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<class URotatingMovementComponent> RotatingMovement;

	virtual void TimerAction();

	UPROPERTY(EditAnywhere, Category = Timer)
	float ActionPeriod;

	FTimerHandle ActionTimer;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

};
