#pragma once

UENUM()
enum class EPlayerNetStatus : uint8
{
    Login,
    Logout,
    Disconnected
};