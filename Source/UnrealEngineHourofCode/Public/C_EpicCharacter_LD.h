// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_EpicCharacter_LD.generated.h"

class AC_Logger;



UCLASS()
class UNREALENGINEHOUROFCODE_API AC_EpicCharacter_LD : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_EpicCharacter_LD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
  TSubclassOf<AActor> spawnIsland;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
  AC_Logger* ACLoggerInstance;

  void SpawnIsland();

};
