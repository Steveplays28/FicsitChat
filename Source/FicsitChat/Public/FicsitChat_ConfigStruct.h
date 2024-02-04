#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigManager.h"
#include "Engine/Engine.h"
#include "FicsitChat_ConfigStruct.generated.h"

struct FFicsitChat_ConfigStruct_ChatMessageColor;

USTRUCT(BlueprintType)
struct FFicsitChat_ConfigStruct_ChatMessageColor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    float Red{};

    UPROPERTY(BlueprintReadWrite)
    float Green{};

    UPROPERTY(BlueprintReadWrite)
    float Blue{};
};

/* Struct generated from Mod Configuration Asset '/FicsitChat/FicsitChat_Config' */
USTRUCT(BlueprintType)
struct FFicsitChat_ConfigStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    FString BotToken{};

    UPROPERTY(BlueprintReadWrite)
    bool HasJoinedMessage{};

    UPROPERTY(BlueprintReadWrite)
    bool HasLeftMessage{};

    UPROPERTY(BlueprintReadWrite)
    FString ChannelId{};

    UPROPERTY(BlueprintReadWrite)
    FFicsitChat_ConfigStruct_ChatMessageColor ChatMessageColor;

    /* Retrieves active configuration value and returns object of this struct containing it */
    static FFicsitChat_ConfigStruct GetActiveConfig(UObject* WorldContext) {
        FFicsitChat_ConfigStruct ConfigStruct{};
        FConfigId ConfigId{"FicsitChat", ""};
        if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull)) {
            UConfigManager* ConfigManager = World->GetGameInstance()->GetSubsystem<UConfigManager>();
            ConfigManager->FillConfigurationStruct(ConfigId, FDynamicStructInfo{FFicsitChat_ConfigStruct::StaticStruct(), &ConfigStruct});
        }
        return ConfigStruct;
    }
};

