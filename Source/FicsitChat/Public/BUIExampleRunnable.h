#pragma once

#include "CoreMinimal.h"
#include "FicsitChat_ConfigStruct.h"
#include "HAL/Runnable.h"

// DECLARE_DYNAMIC(FBUIOnCompleteSignature);

// Note that we do not have to mark our class as UCLASS() if we don't want to
class FBUIExampleRunnable : public FRunnable {
  public:
	// Custom constructor for setting up our thread with its target
	FBUIExampleRunnable(int32 InTargetCount);
	virtual ~FBUIExampleRunnable();

	// FRunnable functions
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	// FRunnable

	// FBUIOnCompleteSignature OnCompleteDelegate;

	bool bBotStarted = false;

  protected:
	FRunnableThread *Thread = nullptr;

	TArray<int32> ProcessedNumbers;

	int32 TargetCount = -1;
	int32 FoundCount = -1;

	bool bStopThread = false;
};
