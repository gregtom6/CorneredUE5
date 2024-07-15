// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBar::NativeConstruct()
{
    Super::NativeConstruct();

    
}

void UHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (Health)
    {
        Health->SetPercent(0.9f); // Example: Set progress to 50%
    }
}