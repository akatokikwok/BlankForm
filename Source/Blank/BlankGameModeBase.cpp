// Copyright Epic Games, Inc. All Rights Reserved.


#include "BlankGameModeBase.h"
#include "CommonTt/GraphTask.h"


void ABlankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Interface = new ITaskInterface();
	NewTask = new ThreadTask();// 独立的一个线程.

	NewTask->ThreadTask_Delegate.BindUObject(this, &ABlankGameModeBase::PrintF);
	NewTask->CreateThread(Interface);

	TGraphTask<FTaskGraph>::CreateTask(nullptr, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(4.5f);
}

void ABlankGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	delete NewTask;

	Interface = nullptr;
}

void ABlankGameModeBase::PrintF()
{
	UE_LOG(LogTemp, Warning, TEXT("ABlankGameModeBase.PrintF."));
}
