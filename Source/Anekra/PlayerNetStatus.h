#pragma once

UENUM()
enum class EPlayerNetStatus : uint8
{
    Disconnected,
    Login,
    Logout,
    Update
};