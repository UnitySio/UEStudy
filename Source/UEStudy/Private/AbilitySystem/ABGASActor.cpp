// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ABGASActor.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/GA/ABGA_Rotate.h"
#include "GameFramework/RotatingMovementComponent.h"

AABGASActor::AABGASActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	ActionPeriod = 3.0f;

}

void AABGASActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* AABGASActor::GetAbilitySystemComponent() const
{
	return ASC;
}

void AABGASActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RotatingMovement->bAutoActivate = false;
	RotatingMovement->Deactivate();

	// OwnerActor: ASC를 구동하고, 데이터를 관리하는 액터
	// AvatarActor: 비주얼 표현을 담당하는 액터
	ASC->InitAbilityActorInfo(this, this);

	FGameplayAbilitySpec RotateSkillSpec(UABGA_Rotate::StaticClass());
	ASC->GiveAbility(RotateSkillSpec);
}

void AABGASActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &AABGASActor::TimerAction, ActionPeriod, true, 0.0f);
	
}

void AABGASActor::TimerAction()
{
	FGameplayAbilitySpec* RotateGASpec = ASC->FindAbilitySpecFromClass(UABGA_Rotate::StaticClass());
	if (!RotateGASpec)
	{
		UE_LOG(LogTemp, Error, TEXT("No Rotate Spec Found!"));
		return;
	}

	if (!RotateGASpec->IsActive())
	{
		ASC->TryActivateAbility(RotateGASpec->Handle);
	}
	else
	{
		ASC->CancelAbilityHandle(RotateGASpec->Handle);
	}
}

