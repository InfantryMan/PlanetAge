// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLevelScript.h"
#include <algorithm>

void AGameLevelScript::GenerateGameField(const int32 cardsNumber)
{

	// Number of cards at X and Y axes
	const int xCardsNum = 3;
	const int yCardsNum = 3;

	// Space between cards by X and Y
	const float dx = (xSize - (AGameCardView::XCardSize * xCardsNum)) / (xCardsNum + 1);
	const float dy = (ySize - (AGameCardView::YCardSize * yCardsNum)) / (yCardsNum + 1);

	// Space between cards by X and Y relative to the origin of maps
	const float xLen = dx + AGameCardView::XCardSize;
	const float yLen = dy + AGameCardView::YCardSize;

	const float topLeftX = 218.3;
	const float topleftY = 107;
	const float topLeftZ = 7;

	FVector topLeftCardPosition(topLeftX, topleftY, topLeftZ);
	FVector currentCardPosition = topLeftCardPosition;
	FRotator cardRotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	if (cardsNumber < 1 || cardsNumber > 9)
	{
		return;
	}

	if (GetWorld())
	{
		const int rowNum = (cardsNumber - 1) / xCardsNum + 1;
		int colNum;
		for (int i = 0; i < rowNum; i++)
		{
			//colNum = (i == rowNum - 1) ? (cardsNumber % xCardsNum) : (xCardsNum);
			colNum = std::min(xCardsNum, cardsNumber - xCardsNum * i);
			for (int j = 0; j < colNum; j++)
			{
				currentCardPosition.X = topLeftCardPosition.X + xLen * j;
				currentCardPosition.Y = topLeftCardPosition.Y + yLen * i;
				if (ToSpawn)
					GetWorld()->SpawnActor<AGameCardView>(ToSpawn, currentCardPosition, cardRotation, spawnParams);
			}
		}
	}
}

void AGameLevelScript::SetScreenResolution(const FIntPoint resolution)
{
	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();

	if (Settings != nullptr)
	{
		Settings->SetScreenResolution(resolution);
	}
	Settings->ApplyResolutionSettings(false);
}
