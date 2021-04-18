// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MySequenceFloatIslandActor.generated.h"

class AC_Logger;
class ALevelSequenceActor;
class ULevelSequence;
class ULevelSequencePlayer;


UCLASS()
class UNREALENGINEHOUROFCODE_API AC_MySequenceFloatIslandActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MySequenceFloatIslandActor();


protected:

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  ALevelSequenceActor* MovieActor;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  ULevelSequencePlayer* LevelSequencePlayer;


  //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
  //ULevelSequence* IntroMovieSequence;

  UPROPERTY(EditAnywhere, Category = "Components", DisplayName = "Critical Hit Chance")
  ULevelSequence* SequenceAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent* MeshComp;

private:
  AC_Logger* ACLoggerInstance;

};
