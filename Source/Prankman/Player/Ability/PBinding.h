#pragma once

UENUM()
enum class EPBinding : uint8
{
    None	UMETA(DisplayName = "None"),
    Confirm	UMETA(DisplayName = "Confirm"),
    Cancel	UMETA(DisplayName = "Cancel"),
    Unlock	UMETA(DisplayName = "Unlock"),
    Ability1	UMETA(DisplayName = "Ability1"),
    Ability2	UMETA(DisplayName = "Ability2"),
    Ability3	UMETA(DisplayName = "Ability3"),
    Ability4	UMETA(DisplayName = "Ability4"),
    Passive1	UMETA(DisplayName = "None"),
    Passive2	UMETA(DisplayName = "None")
};