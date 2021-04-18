// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Logger.h"

// Sets default values
AC_Logger::AC_Logger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Logger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Logger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AC_Logger::printToScreen(float lifeTime, FColor color, const FString & DebugMessage)
{
  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(-1, lifeTime, color, DebugMessage);
  }

}

