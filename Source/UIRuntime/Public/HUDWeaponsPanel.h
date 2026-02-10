// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWeaponsPanel.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChangedEvent, FString, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponAmmoChanged, int , CurrentAmmo , int , MaxAmmo);

UCLASS()
class UIRUNTIME_API UHUDWeaponsPanel : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintAssignable)
	FOnWeaponChangedEvent OnWeaponChangedEvent;
	
	UPROPERTY(BlueprintAssignable)
	FOnWeaponAmmoChanged OnWeaponAmmoChanged;
	
public:
	
	void InvokeOnWeaponChangedEvent(FString WeaponName);
	void InvokeOnWeaponAmmoChangedEvent(int CurrentAmmo , int MaxAmmo);
};
