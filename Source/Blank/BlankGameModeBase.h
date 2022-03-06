// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CommonTt/TaskInterface.h"
#include "CommonTt/ThreadTask.h"
#include "BlankGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class BLANK_API ABlankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	//
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void PrintF();
public:
	class ITaskInterface* Interface;
	class ThreadTask* NewTask;
};
