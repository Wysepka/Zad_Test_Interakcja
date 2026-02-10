// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWeaponsPanel.h"

void UHUDWeaponsPanel::InvokeOnWeaponChangedEvent(FString WeaponName)
{
	if (OnWeaponChangedEvent.IsBound())
	{
		OnWeaponChangedEvent.Broadcast(WeaponName);
	}
}

void UHUDWeaponsPanel::InvokeOnWeaponAmmoChangedEvent(int CurrentAmmo, int MaxAmmo)
{
	if (OnWeaponAmmoChanged.IsBound())
	{
		OnWeaponAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
	}
}
