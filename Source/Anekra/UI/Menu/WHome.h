#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemTypes.h"
#include "Blueprint/UserWidget.h"
#include "WHome.generated.h"


UCLASS()
class ANEKRA_API UWHome : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UWFriends* WFriends;


};