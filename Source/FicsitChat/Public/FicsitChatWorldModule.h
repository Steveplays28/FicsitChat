#pragma once

#include "CoreMinimal.h"
#include "FicsitChat_ConfigStruct.h"
#include "Module/GameWorldModule.h"
#include "Modules/ModuleManager.h"

// DPP (and WindowsHWrapper)
#include "Windows/WindowsHWrapper.h"

THIRD_PARTY_INCLUDES_START
#include "dpp/dpp.h"
THIRD_PARTY_INCLUDES_END

//
#include "FicsitChatWorldModule.generated.h"

UCLASS()
class UFicsitChatWorldModule : public UGameWorldModule {
	GENERATED_BODY()

  public:
	UFicsitChatWorldModule();
	virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;

	void SendMessageToGame(FString messageContent, FString messageAuthor);

	TSharedPtr<dpp::cluster> bot;
};
