#pragma once

UENUM()
enum class EEventPhase : uint8
{
    Start,
    Step,
    Stop
};

UENUM()
enum class EEventType : uint8
{
    None,
    StopMove,
    //FindColor,
    Snake,
    Count
};