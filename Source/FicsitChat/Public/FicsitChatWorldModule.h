#pragma once

#include "CoreMinimal.h"
#include "FicsitChat_ConfigStruct.h"
#include "Module/GameWorldModule.h"
#include "Modules/ModuleManager.h"
//
#include "FicsitChatWorldModule.generated.h"

UCLASS()
class UFicsitChatWorldModule : public UGameWorldModule {
	GENERATED_BODY()

  public:
	UFicsitChatWorldModule();
	virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;
};
