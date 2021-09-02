#pragma once

constexpr struct Game
{
    struct
    {
        struct
        {
            float CastingTime = 1.f;
        } Unlock;
    } Ability;

    struct
    {
        int AbilitiesCount = 4;

    } Player;

    struct
    {
        int CellCountX = 10;
        float CellSize = 800.f;
    } Map;
} Game;