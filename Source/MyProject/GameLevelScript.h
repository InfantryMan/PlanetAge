// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "GameCardView.h"
#include "GameFramework/GameUserSettings.h"
#include <Kismet/GameplayStatics.h>
#include "GameLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AGameLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

protected:

	// Size of GameField
	float xSize = 1635;
	float ySize = 1070;
	float zSize = 5;

	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<AGameCardView> ToSpawn;

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void GenerateGameField(const int32 cardsNumber);

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void SetScreenResolution(const FIntPoint resolution);

};
