#include "BoxSpawner.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "TargetBox.h"

ABoxSpawner::ABoxSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();

	FetchJSONData();
}

void ABoxSpawner::FetchJSONData()
{
	FHttpModule* Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetURL("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
	Request->SetVerb("GET");

	Request->OnProcessRequestComplete().BindUObject(this, &ABoxSpawner::OnResponseReceived);

	Request->ProcessRequest();
}

void ABoxSpawner::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
		return;
	}

	FString ResponseString = Response->GetContentAsString();

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("JSON Parsed Successfully"));

		// Access types array
		const TArray<TSharedPtr<FJsonValue>>* TypesArray;

		if (JsonObject->TryGetArrayField("types", TypesArray))
		{
			for (const TSharedPtr<FJsonValue>& TypeValue : *TypesArray)
			{
				TSharedPtr<FJsonObject> TypeObject = TypeValue->AsObject();

				FString Name = TypeObject->GetStringField("name");

				TArray<TSharedPtr<FJsonValue>> ColorArray = TypeObject->GetArrayField("color");

				FBoxTypeData BoxData;

				BoxData.Color = FColor(
					ColorArray[0]->AsNumber(),
					ColorArray[1]->AsNumber(),
					ColorArray[2]->AsNumber()
				);

				BoxData.Health = TypeObject->GetIntegerField("health");
				BoxData.Score = TypeObject->GetIntegerField("score");

				TypeDataMap.Add(Name, BoxData);
			}
		}

		// Access objects array
		const TArray<TSharedPtr<FJsonValue>>* ObjectsArray;

		if (JsonObject->TryGetArrayField("objects", ObjectsArray))
		{
			for (const TSharedPtr<FJsonValue>& ObjValue : *ObjectsArray)
			{
				TSharedPtr<FJsonObject> Obj = ObjValue->AsObject();

				TSharedPtr<FJsonObject> Transform;

				if (!Obj->HasField("transform"))
				{
					continue;
				}

				Transform = Obj->GetObjectField("transform");

				FString TypeName = Obj->GetStringField("type");

				const TArray<TSharedPtr<FJsonValue>>* LocationArray;
				const TArray<TSharedPtr<FJsonValue>>* RotationArray;
				const TArray<TSharedPtr<FJsonValue>>* ScaleArray;

				if (!Transform->TryGetArrayField("location", LocationArray)) continue;
				if (!Transform->TryGetArrayField("rotation", RotationArray)) continue;
				if (!Transform->TryGetArrayField("scale", ScaleArray)) continue;

				FVector Location(
					(*LocationArray)[0]->AsNumber(),
					(*LocationArray)[1]->AsNumber(),
					(*LocationArray)[2]->AsNumber()
				);

				FRotator Rotation(
					(*RotationArray)[1]->AsNumber(),
					(*RotationArray)[2]->AsNumber(),
					(*RotationArray)[0]->AsNumber()
				);

				FVector Scale(
					(*ScaleArray)[0]->AsNumber(),
					(*ScaleArray)[1]->AsNumber(),
					(*ScaleArray)[2]->AsNumber()
				);

				if (TargetBoxClass)
				{
					FActorSpawnParameters SpawnParams;

					ATargetBox* SpawnedBox = GetWorld()->SpawnActor<ATargetBox>(
						TargetBoxClass,
						Location,
						Rotation,
						SpawnParams
					);

					if (SpawnedBox)
					{
						SpawnedBox->SetActorScale3D(Scale);

						if (TypeDataMap.Contains(TypeName))
						{
							FBoxTypeData BoxData = TypeDataMap[TypeName];

							SpawnedBox->Health = BoxData.Health;
							SpawnedBox->Score = BoxData.Score;

							SpawnedBox->SetBoxColor(BoxData.Color);
						}
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed"));
	}
}