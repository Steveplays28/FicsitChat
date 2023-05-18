#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigManager.h"
#include "Engine/Engine.h"
#include "FicsitChat_ConfigStruct.generated.h"

/* Struct generated from Mod Configuration Asset '/FicsitChat/FicsitChat_Config' */
USTRUCT(BlueprintType)
struct FFicsitChat_ConfigStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    FString BotToken;

    UPROPERTY(BlueprintReadWrite)
    bool HasJoinedMessage;

    UPROPERTY(BlueprintReadWrite)
    bool HasLeftMessage;

    /* Retrieves active configuration value and returns object of this struct containing it */
    static FFicsitChat_ConfigStruct GetActiveConfig() {
        FFicsitChat_ConfigStruct ConfigStruct{};
        FConfigId ConfigId{"FicsitChat", ""};
        UConfigManager* ConfigManager = GEngine->GetEngineSubsystem<UConfigManager>();
        ConfigManager->FillConfigurationStruct(ConfigId, FDynamicStructInfo{FFicsitChat_ConfigStruct::StaticStruct(), &ConfigStruct});
        return ConfigStruct;
    }
};

