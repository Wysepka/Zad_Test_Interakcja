// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDWeaponsPanel.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "UMessagingBus.h"
#include "UHUDInteractPopup.h"
#include "HUDInteraction.generated.h"

/**
 * 
 */
UCLASS()
class UIRUNTIME_API AHUDInteraction : public AHUD
{
	GENERATED_BODY()
	
private:
	void OnPlayerInteractionStartedHit(FInteractionEventData Data);
	void OnPlayerInteractionEndedHit();
	
	void OnWeaponChanged(FString WeaponName);
	void OnWeaponAmmoChanged(int CurrentAmmo , int MaxAmmo);
	
	void GetMessagingBus();
	bool InitializeInteractionPopup(APlayerController* PC);
	bool InitializeWeaponsPanel(APlayerController* PC);
	
	TObjectPtr<UHUDInteractPopup> InteractionPopupInstance;
	TObjectPtr<UHUDWeaponsPanel> WeaponsPanelInstance;

public:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Interaction")
	TSubclassOf<UHUDInteractPopup> InteractionPopupClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Interaction")
	TSubclassOf<UHUDWeaponsPanel> WeaponsPanelClass;
	
};
