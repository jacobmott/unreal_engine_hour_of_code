// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_MyGameStateBase.generated.h"



class AC_Logger;
/**
 * 
 */
UCLASS()
class UNREALENGINEHOUROFCODE_API AC_MyGameStateBase : public AGameStateBase
{

	GENERATED_BODY()


public:
  // Accessor for C++ & BP. Should be self-explanatory
  //UFUNCTION(BlueprintPure, Category = "Persistence", meta = (DisplayName = "Get Savegame Manager", Keywords = "SavegameManager"))
  AC_Logger* getLogger();


public:
  virtual void HandleBeginPlay() override;
  void setPlayerSpawnLocation(FVector location);

  void respawn();

protected:
  UFUNCTION()
  void WhenPlayerDestroyed(AActor* DestroyedActor);


private:
  // Needs to be an UPROPERTY(), so the GC does its thing
  // Transient, so it doesn't get serialized itself. Will be nulled when the
  // game starts. Initialization happens later by hand.
  UPROPERTY(Transient)
  AC_Logger* ACLoggerInstance;

  FVector playerLocation;
	
};
