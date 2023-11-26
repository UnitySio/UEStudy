// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HpBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class UESTUDY_API UHpBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void SetHpPercent(float Percent);

private:
	UPROPERTY()
	class UHpBar* HpBarWidget;
	
};
