#include "UHUDInteractPopup.h"

void UHUDInteractPopup::InvokeOnInteractionSetTextEvent(FString DisplayName)
{
	if (OnInteractionSetTextEvent.IsBound())
	{
		OnInteractionSetTextEvent.Broadcast(DisplayName);
	}
}