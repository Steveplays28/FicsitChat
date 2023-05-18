#pragma once

#include "CoreMinimal.h"
#include "FicsitChat_ConfigStruct.h"
#include "HAL/Runnable.h"

class FBUIExampleRunnable : public FRunnable {
  public:
	FBUIExampleRunnable();
	virtual ~FBUIExampleRunnable();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

  protected:
	FRunnableThread *Thread = nullptr;
};
