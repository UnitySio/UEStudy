// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "Components/SphereComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap); // SphereComponent의 OnComponentBeginOverlap 이벤트에 OnSphereOverlap 함수를 바인딩
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap); // SphereComponent의 OnComponentEndOverlap 이벤트에 OnSphereEndOverlap 함수를 바인딩
	
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

