// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Character/ABGASUEStudyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Character/ABGASPlayerState.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AABGASUEStudyCharacter::AABGASUEStudyCharacter()
{
	ASC = nullptr;
}

UAbilitySystemComponent* AABGASUEStudyCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AABGASUEStudyCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AABGASUEStudyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AABGASPlayerState* GASPS = GetPlayerState<AABGASPlayerState>();
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		int32 InputId = 0;
		for (const auto& StartAbility : StartAbilities)
		{
			// 어빌리티 정보
			FGameplayAbilitySpec StartSpec(StartAbility);
			StartSpec.InputID = InputId++;
			ASC->GiveAbility(StartSpec);
		}

		for (const auto& StartInputAbility : StartInputAbilities)
		{
			// 어빌리티 정보
			FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
			StartSpec.InputID = StartInputAbility.Key;
			ASC->GiveAbility(StartSpec);
		}
		
		SetupGASInputComponent();

		APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
		PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}
}

void AABGASUEStudyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	SetupGASInputComponent();
}

void AABGASUEStudyCharacter::SetupGASInputComponent()
{
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AABGASUEStudyCharacter::GASInputPressed, 0);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AABGASUEStudyCharacter::GASInputReleased, 0);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AABGASUEStudyCharacter::GASInputPressed, 1);
	}
}

void AABGASUEStudyCharacter::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void AABGASUEStudyCharacter::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}
