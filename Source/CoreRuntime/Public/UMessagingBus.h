#pragma once
#include "IPickable.h"
#include "UMessagingBus.generated.h"

USTRUCT(BlueprintType)
struct FInteractionEventData
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AActor> TargetPickable;
};

DECLARE_MULTICAST_DELEGATE(FOnInteractionResetStatic);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionDataStatic, FInteractionEventData);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPickableInteractedStatic , FInteractionEventData);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponChangedStatic , FString);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWeaponAmmoChangedStatic , int, int);

UCLASS()
class CORERUNTIME_API UMessagingBus : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	void BroadcastInteractionDataStart(FInteractionEventData Data);
	void BroadcastInteractionDataReset();
	
	void BroadcastPickableInteracted(FInteractionEventData EventData);
	
	void BroadcastOnWeaponChanged(FString WeaponName);
	void BroadcastOnAmmoChanged(int CurrentAmmo , int MaxAmmo);
	
	FOnInteractionDataStatic OnInteractionDataStartEvent_Static;
	FOnInteractionResetStatic OnInteractionDataResetEvent_Static;
	
	FOnPickableInteractedStatic OnPickableInteractedEvent_Static;
	
	FOnWeaponChangedStatic OnWeaponChangedEvent_Static;
	FOnWeaponAmmoChangedStatic OnAmmoChangedEvent_Static;
};
