// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TObjectPtr<UMessagingBus> UPlayerInventory::GetMessagingBus()
{
	ULocalPlayer* LP = GetWorld()->GetFirstLocalPlayerFromController();
	
	if (LP == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get LocalPlayer from %s") , *GetName() ));
		UE_LOG(LogTemp, Warning, TEXT("Could not get LocalPlayer from %s") , *GetName()) ;
		return nullptr;
	}
	
	UMessagingBus* MessagingBus = LP->GetSubsystem<UMessagingBus>();
	if (MessagingBus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 10.f , FColor::Red , FString::Printf(TEXT("Could not get MessagingBus from %s") , *GetName() ));
		UE_LOG(LogTemp, Warning, TEXT("Could not get MessagingBus from %s") , *GetName() ) ;
	}
	
	return MessagingBus;
}

void UPlayerInventory::Interact(TScriptInterface<UIPickable> Pickable)
{
	UObject* PickableObj = Pickable.GetObject();
	FString PickableID = IIPickable::Execute_GetPickableID(PickableObj);
	EPickableType PickableType = IIPickable::Execute_GetPickableType(PickableObj);
	FString DisplayName = IIPickable::Execute_GetDisplayName(PickableObj);
	if (PickableType == EPickableType::Weapon)
	{
		if (!InventorySlots.Contains(PickableID))
		{
			if (PickableType == EPickableType::Weapon)
			{
				int MaxAmmo = IIPickable::Execute_GetMaxAmmo(PickableObj);
				int StartAmmo = IIPickable::Execute_GetStartAmmo(PickableObj);
				TSharedPtr<FInventorySlot> NewInventorySlot = MakeShared<FInventorySlot>(PickableID , MaxAmmo , StartAmmo);
				InventorySlots.Add(PickableID , NewInventorySlot);
				CurrentInventorySlot = NewInventorySlot;
				
				GetMessagingBus()->BroadcastOnWeaponChanged(DisplayName);
				GetMessagingBus()->BroadcastOnAmmoChanged(StartAmmo , MaxAmmo);
			}
		}
		else
		{
			if (CurrentInventorySlot->PickableID != PickableID)
			{
				CurrentInventorySlot = InventorySlots[PickableID];
				
				GetMessagingBus()->BroadcastOnWeaponChanged(DisplayName);
				GetMessagingBus()->BroadcastOnAmmoChanged(CurrentInventorySlot->CurrentAmmo , CurrentInventorySlot->MaxAmmo);
			}
		}
	}
	else
	{
		if (InventorySlots.Contains(PickableID))
		{
			int AmmoPickup = IIPickable::Execute_GetAmmoPickupCount(PickableObj);
			int CurrentAmmo = InventorySlots[PickableID]->CurrentAmmo;
			int MaxAmmo = InventorySlots[PickableID]->MaxAmmo;
			int AmmountToAdd = FMath::Min(AmmoPickup , MaxAmmo - CurrentAmmo);
			InventorySlots[PickableID]->CurrentAmmo += AmmountToAdd;
		}
		
		if (CurrentInventorySlot != nullptr && CurrentInventorySlot->PickableID ==  PickableID)
		{
			GetMessagingBus()->BroadcastOnAmmoChanged(CurrentInventorySlot->CurrentAmmo , CurrentInventorySlot->MaxAmmo);
		}
	}
}


