// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDInteraction.h"

void AHUDInteraction::OnPlayerInteractionStartedHit(FInteractionEventData Data)
{
	InteractionPopupInstance->SetVisibility(ESlateVisibility::Visible);
	InteractionPopupInstance->SetRenderOpacity(1.f);
	
	FString DisplayName = FString("Invalid");
	
	if (Data.TargetPickable && Data.TargetPickable->Implements<UIPickable>())
	{
		DisplayName = IIPickable::Execute_GetDisplayName(Data.TargetPickable);
	}	
	InteractionPopupInstance->InvokeOnInteractionSetTextEvent(DisplayName);
}

void AHUDInteraction::OnPlayerInteractionEndedHit()
{
	InteractionPopupInstance->SetVisibility(ESlateVisibility::Hidden);
	InteractionPopupInstance->SetRenderOpacity(0.f);
}

void AHUDInteraction::OnWeaponChanged(FString WeaponName)
{
	WeaponsPanelInstance->InvokeOnWeaponChangedEvent(WeaponName);
}

void AHUDInteraction::OnWeaponAmmoChanged(int CurrentAmmo, int MaxAmmo)
{
	WeaponsPanelInstance->InvokeOnWeaponAmmoChangedEvent(CurrentAmmo, MaxAmmo);
}

void AHUDInteraction::GetMessagingBus()
{
	ULocalPlayer* LP = GetWorld()->GetFirstLocalPlayerFromController();
	
	if (LP == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get LocalPlayer from %s") , *GetName() ));
		UE_LOG(LogTemp, Warning, TEXT("Could not get LocalPlayer from %s") , *GetName()) ;
		return;
	}
	
	UMessagingBus* MessagingBus = LP->GetSubsystem<UMessagingBus>();
	if (MessagingBus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get MessagingBus from %s") , *GetName() ));
		UE_LOG(LogTemp, Warning, TEXT("Could not get MessagingBus from %s") , *GetName() ) ;
	}
	
	MessagingBus->OnInteractionDataStartEvent_Static.AddUObject(this, &AHUDInteraction::OnPlayerInteractionStartedHit);
	MessagingBus->OnInteractionDataResetEvent_Static.AddUObject(this, &AHUDInteraction::OnPlayerInteractionEndedHit);
	
	MessagingBus->OnWeaponChangedEvent_Static.AddUObject(this, &AHUDInteraction::OnWeaponChanged);
	MessagingBus->OnAmmoChangedEvent_Static.AddUObject(this, &AHUDInteraction::OnWeaponAmmoChanged);
}

bool AHUDInteraction::InitializeInteractionPopup(APlayerController* PC)
{
	if (!InteractionPopupClass)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("No InteractionPopupClass set in HUD"));
		UE_LOG(LogTemp, Warning, TEXT("InteractionPopupClass not set on HUD"));
		return true;
	}
	
	InteractionPopupInstance = CreateWidget<UHUDInteractPopup>(PC, InteractionPopupClass);
	if (InteractionPopupInstance)
	{
		InteractionPopupInstance->AddToViewport();
		InteractionPopupInstance->SetVisibility(ESlateVisibility::Hidden);
	}
	return false;
}

bool AHUDInteraction::InitializeWeaponsPanel(APlayerController* PC)
{
	if (!WeaponsPanelClass)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , TEXT("No WeaponsPanelClass set in HUD"));
		UE_LOG(LogTemp, Warning, TEXT("WeaponsPanelClass not set on HUD"));
		return true;
	}
	
	WeaponsPanelInstance = CreateWidget<UHUDWeaponsPanel>(PC, WeaponsPanelClass);
	if (WeaponsPanelInstance)
	{
		WeaponsPanelInstance->AddToViewport();
	}
	return false;
}

void AHUDInteraction::BeginPlay()
{
	Super::BeginPlay();
	
	GetMessagingBus();

	APlayerController* PC = GetOwningPlayerController();
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerController"));
		UE_LOG(LogTemp, Warning, TEXT("No PlayerController for HUD"));
		return;
	}
	
	InitializeInteractionPopup(PC);
	
	InitializeWeaponsPanel(PC);
}
