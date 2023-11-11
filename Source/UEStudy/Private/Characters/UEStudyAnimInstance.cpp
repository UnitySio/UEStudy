// Fill out your copyright notice in the Description page of Project Settings.


#include "UEStudy/Public/Characters/UEStudyAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UEStudy/Public/Characters/UEStudyCharacter.h"

void UUEStudyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UEStudyCharacter = Cast<AUEStudyCharacter>(TryGetPawnOwner());
	if (UEStudyCharacter)
	{
		MovementComponent = UEStudyCharacter->GetCharacterMovement();
	}
}

void UUEStudyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		IsFalling = MovementComponent->IsFalling();
	}
}
