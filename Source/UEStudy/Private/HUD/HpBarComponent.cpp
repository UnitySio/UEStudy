// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HpBarComponent.h"

#include "Components/ProgressBar.h"
#include "HUD/HpBar.h"

void UHpBarComponent::SetHpPercent(float Percent)
{
	if (HpBarWidget == nullptr)
	{
		HpBarWidget = Cast<UHpBar>(GetUserWidgetObject());
	}
	
	if (HpBarWidget && HpBarWidget->HpBar)
	{
		HpBarWidget->HpBar->SetPercent(Percent);
	}
}
