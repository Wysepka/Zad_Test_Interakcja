#include "UMessagingBus.h"

void UMessagingBus::BroadcastInteractionDataStart(FInteractionEventData Data)
{
	if (OnInteractionDataStartEvent_Static.IsBound())
	{
		OnInteractionDataStartEvent_Static.Broadcast(Data);
	}
}

void UMessagingBus::BroadcastInteractionDataReset()
{
	if (OnInteractionDataResetEvent_Static.IsBound())
	{
		OnInteractionDataResetEvent_Static.Broadcast();
	}
}

void UMessagingBus::BroadcastPickableInteracted(FInteractionEventData EventData)
{
	if (OnPickableInteractedEvent_Static.IsBound())
	{
		OnPickableInteractedEvent_Static.Broadcast(EventData);
	}
}

void UMessagingBus::BroadcastOnWeaponChanged(FString WeaponName)
{
	if (OnWeaponChangedEvent_Static.IsBound())
	{
		OnWeaponChangedEvent_Static.Broadcast(WeaponName);
	}
}

void UMessagingBus::BroadcastOnAmmoChanged(int CurrentAmmo, int MaxAmmo)
{
	if (OnAmmoChangedEvent_Static.IsBound())
	{
		OnAmmoChangedEvent_Static.Broadcast(CurrentAmmo, MaxAmmo);
	}
}
