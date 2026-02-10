#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCoreRuntimeModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
