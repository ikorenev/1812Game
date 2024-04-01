#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PieceOrderWidgetComponent.generated.h"

UCLASS(BlueprintType)
class GAME1812_API UPieceOrderWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UPieceOrderWidgetComponent();

protected:

	class APiece* OwnerPiece;

	virtual void BeginPlay() override;
	
public:

	void OnEnable();
	void OnDisable();
};
