// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPickable.generated.h"

UENUM(BlueprintType)
enum class EPickableType : uint8
{
	Invalid    UMETA(DisplayName = "Invalid"),
	Ammo       UMETA(DisplayName = "Ammo"),
	Weapon     UMETA(DisplayName = "Weapon"),
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIPickable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CORERUNTIME_API IIPickable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Pickable")
	FString GetDisplayName() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Pickable")
	FString GetPickableID() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Pickable")
	EPickableType GetPickableType() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Pickable")
	int GetMaxAmmo() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Pickable")
	int GetStartAmmo() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Pickable")
	int GetAmmoPickupCount() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Pickable")
	void Interact();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
