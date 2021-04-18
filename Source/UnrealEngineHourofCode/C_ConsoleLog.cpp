// Fill out your copyright notice in the Description page of Project Settings.

// define a print message function to print to screen
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, FString::Printf(TEXT(text), fstring))
#include "C_ConsoleLog.h"

// Sets default values
AC_ConsoleLog::AC_ConsoleLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_ConsoleLog::BeginPlay()
{
  Super::BeginPlay();

  // Standard way to log to console.
  UE_LOG(LogTemp, Warning, TEXT("I just started running"));

  // Log to Screen
  GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Screen Message"));

  FVector MyVector = FVector(200, 100, 900);

  // log vector
  GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("My Location is: %s"), *GetActorLocation().ToString()));

  // Use the shortcut defined above
  print("Hello Unreal");
  printFString("My Variable Vector is: %s", *MyVector.ToString());
	
}

// Called every frame
void AC_ConsoleLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

