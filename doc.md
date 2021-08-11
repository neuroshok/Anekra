# Hero
- Collect cell : get a chance to obtain an ability
## Ability
### Active ability
- trap a cell : Display an effect on the cell according to the trap
  - drain : steal hp from a player on the same cell
  - bomb : give a bomb, X seconds before explosion

### Passive ability (during X seconds)
- double jump

# World
## Event
Triggers every X secondes
- Player has X second to find & stay on a specific color cell or symbol
- Player must change cell every 2sec, without reusing the same cell of any player

## Cell
### Property
- Passive : trigger when the player is over
- Cyclic : trigger every X seconds
- Delay : trigger after X seconds

### Type
- Rotating cell
- Ghost cell : Cell disappear when someone stay over, then the player fall, reappear when someoneleft