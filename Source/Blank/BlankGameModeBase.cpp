// Copyright Epic Games, Inc. All Rights Reserved.


#include "BlankGameModeBase.h"
#include "CommonTt/GraphTask.h"
#include "CommonTt/MyAsyncTask.h"


void ABlankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Interface = new ITaskInterface();
	NewTask = new ThreadTask();// 独立的一个线程.

	NewTask->ThreadTask_Delegate.BindUObject(this, &ABlankGameModeBase::PrintF);
	NewTask->CreateThread(Interface);

	/**
* Runanable真正意义上的线程,用于复杂计算,比如数据库,服务器
TGraphTask有一个特点,是支持任务顺序的, 简单的计算,但是比较卡游戏线程时间
FAsyncTask 会主动创十几个线程,如果没有任务的话,就会把任务放到闲置的AsyncTask里执行,注意,这些线程都是直接被创建好的;用于做复杂计算
注意,使用SpawnActor, NewObject, DestroyActor/Object DrawDebugline必须是在主线程里,禁止在别的线程里用.
	 */


	/* 供TGraphTask去使用的 自定义的线程任务.*/
	TGraphTask<FTaskGraph>::CreateTask(nullptr, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(4.5f);

	/* 供FAsyncTask去使用的 自定义线程任务 */
	FAsyncTask<TaskAsyncTask>* MyTask = new FAsyncTask<TaskAsyncTask>(3);
	MyTask->StartBackgroundTask();
	if (MyTask->IsDone()) {
		UE_LOG(LogTemp, Log, TEXT("MyTask->IsDone()"));
	}
	MyTask->EnsureCompletion();
	delete MyTask;
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
