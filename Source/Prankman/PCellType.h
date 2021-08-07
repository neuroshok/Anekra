#pragma once

UENUM()
enum class EPCellType : uint8
{
    Basic,
    Rotating, // rotating
    Slow, // player on the cell are slow
    Ghost, // after X seconds with players over it, the cell lost collisions
    Vanish, // disappear definitely after X seconds
    Heal, // heal all players
    Teleport, // teleport to a random cell
    Count
};