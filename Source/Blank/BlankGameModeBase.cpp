// Copyright Epic Games, Inc. All Rights Reserved.


#include "BlankGameModeBase.h"


void ABlankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Interface = new ITaskInterface();
	NewTask = new ThreadTask();// 线程.

	NewTask->CreateThread(Interface);
	NewTask->ThreadTask_Delegate.BindUObject(this, &ABlankGameModeBase::PrintF);
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
