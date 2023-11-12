// Fill out your copyright notice in the Description page of Project Settings.


#include "UEStudy/Public/Characters/UEStudyCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Weapons/Weapon.h"

AUEStudyCharacter::AUEStudyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false; // Pitch를 컨트롤러로 회전시키지 않음
	bUseControllerRotationYaw = false; // Yaw를 컨트롤러로 회전시키지 않음
	bUseControllerRotationRoll = false; // Roll을 컨트롤러로 회전시키지 않음

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동방향으로 회전시킴
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // 회전속도 설정

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent()); // Spring Arm을 RootComponent의 자식으로 설정
	CameraBoom->TargetArmLength = 500.f; // Spring Arm의 길이 설정

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(FName("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom); // Camera를 Spring Arm의 자식으로 설정

}

void AUEStudyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 무기 장착
	SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponActor);
	if (SpawnedWeapon)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		SpawnedWeapon->AttachToComponent(GetMesh(), TransformRules, FName("hand_socket_R"));
	}
	
}

void AUEStudyCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator ControlRotation = GetControlRotation(); // 컨트롤러의 회전값을 가져옴
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f); // Pitch, Roll을 0으로 설정
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // X축을 기준으로 이동방향을 설정
		
		AddMovementInput(Direction, Value); // 이동방향으로 이동
	}
}

void AUEStudyCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator ControlRotation = GetControlRotation(); // 컨트롤러의 회전값을 가져옴
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f); // Pitch, Roll을 0으로 설정
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Y축을 기준으로 이동방향을 설정
		
		AddMovementInput(Direction, Value); // 이동방향으로 이동
	}
}

void AUEStudyCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AUEStudyCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AUEStudyCharacter::EKeyPressed()
{
	if (OverlappingItem)
	{
		AWeapon* Weapon = Cast<AWeapon>(OverlappingItem);
		if (Weapon)
		{
			Weapon->Equip(GetMesh(), FName("hand_socket_R"));
		}
	}
}

void AUEStudyCharacter::Attack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		int32 Selection = FMath::RandRange(0, 4);
		FString Section = FString::Printf(TEXT("Attack %d"), Selection);
		AnimInstance->Montage_JumpToSection(FName(*Section), AttackMontage);
	}
}

void AUEStudyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUEStudyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AUEStudyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AUEStudyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AUEStudyCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AUEStudyCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AUEStudyCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AUEStudyCharacter::Attack);

}

