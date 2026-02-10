// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPickable.h"
#include "Components/ActorComponent.h"
#include "UMessagingBus.h"
#include "PlayerInventory.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FString PickableID;
	
	UPROPERTY(BlueprintReadWrite)
	int MaxAmmo;
	
	UPROPERTY(BlueprintReadWrite)
	int CurrentAmmo;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTORS_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact(TScriptInterface<UIPickable> Pickable);
	
	TObjectPtr<UMessagingBus> GetMessagingBus();
	
private:
	TMap<FString, TSharedPtr<FInventorySlot>> InventorySlots;
	TSharedPtr<FInventorySlot> CurrentInventorySlot;
};
