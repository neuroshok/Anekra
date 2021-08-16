# Lore
The player is a mage exploring temples to find antic magic
Spells are protected by runic locks, mages try to unlock them.
They use their spells and unlocked spells to fight ennemies or trap other runes

Dans un futur lointain, les Terriens ont découvert que les légendes sur la magie étaient
une connaissance ancestrale qui se perdit à travers le temps. Lors des explorations spatiales,
les Terriens ont découvert des planètes avec les vestiges de temples consacrés à 
cette connaissance. Pensant d'abord à des technologies avancées, les études ont ensuite montrées
que les phénomènes magiques étaient directement liés à l'univers. Après de nombreuses années
de recherche, les premiers mages firent leur apparition après avoir trouvé comment lier leur
être au flux d'énergie magique de l'univers.

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