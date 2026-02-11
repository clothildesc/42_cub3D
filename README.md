# Cub3D

A 3D game engine inspired by the legendary **Wolfenstein 3D**, the first FPS ever made. This project uses raycasting to create a dynamic 3D view inside a maze from a first-person perspective.

## 📋 Description

**Cub3D** is a 42 School project that introduces students to the fundamentals of raycasting, graphics programming, and game development. Inspired by the iconic Wolfenstein 3D (1992), this project demonstrates:

- **Raycasting algorithm** for 3D rendering
- Real-time graphics with **MiniLibX**
- Map parsing and validation
- Texture mapping
- Player movement and collision detection
- Event handling (keyboard and mouse)

This project recreates the immersive experience of navigating through a 3D maze using only 2D map data and mathematical projections.

**🤝 This project was developed in collaboration with [@BenjaminSuger](https://github.com/BenjaminSuger).**

**📦 Original repository: [BenjaminSuger/CUB3D](https://github.com/BenjaminSuger/CUB3D)**

<img width="1183" height="807" alt="image" src="https://github.com/user-attachments/assets/bac0edbc-625d-47b5-a0c2-85147a8a116c" />

## 🚀 Features

### Mandatory Part
- **First-person 3D rendering** using raycasting
- **Textured walls** with different textures for each cardinal direction (North, South, East, West)
- **Floor and ceiling colors** (configurable via RGB)
- **Smooth player movement**:
  - `W`, `A`, `S`, `D` keys for movement
  - Arrow keys or mouse for camera rotation
- **Collision detection** with walls
- **Map parsing** from `.cub` configuration files
- **Window management** (close with ESC or window close button)

### Bonus Features ✨
- **Minimap** with real-time player position and field of view
- **Animated doors** that can be opened/closed
- **Mouse controls** for camera rotation
- **Enhanced textures** and visual effects
- **Teleportation doors** (special door mechanics)

## 📁 Project Structure

```
.
├── Makefile                    # Build configuration
├── maps/                       # Map files (.cub)
├── textures/                   # Wall texture assets
├── libft/                      # Custom C library
├── cub3d_mandatory/           # Mandatory part
│   ├── includes/
│   │   ├── cub3d.h           # Main structures
│   │   ├── game.h            # Game engine functions
│   │   └── parsing.h         # Map parsing
│   ├── sources/
│   │   ├── game/             # Game engine
│   │   │   ├── cast_rays.c   # Raycasting algorithm
│   │   │   ├── display_game.c
│   │   │   ├── run_game.c
│   │   │   └── manage_moves.c
│   │   └── parsing/          # Map validation
│   └── main.c
└── cub3d_bonus/               # Bonus part
    ├── includes/
    ├── sources/
    │   ├── game/
    │   ├── minimap/          # Minimap rendering
    │   ├── door/             # Door mechanics
    │   └── parsing/
    └── main_bonus.c
```

## 🎮 Map File Format

Maps are defined in `.cub` files with the following format:

```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,230,220

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Symbols:
- `0` - Empty space (walkable)
- `1` - Wall
- `N`, `S`, `E`, `W` - Player starting position and orientation
- `D` - Door (bonus)

## 🔧 Installation

### Prerequisites
- GCC or Clang compiler
- Make
- MiniLibX (included or system-installed)
- X11 (Linux) or macOS graphics libraries

### Compilation

**Mandatory version:**
```bash
git clone https://github.com/clothildesc/42_cub3D.git
cd 42_cub3D
make
```

**Bonus version:**
```bash
make bonus
```

This generates the `cub3D` or `cub3D_bonus` executable.

### Make Commands
- `make` - Compile mandatory version
- `make bonus` - Compile bonus version
- `make clean` - Remove object files
- `make fclean` - Remove object files and executables
- `make re` - Recompile from scratch

## 💻 Usage

### Running the Game

```bash
./cub3D maps/map.cub
```

**Bonus version:**
```bash
./cub3D_bonus maps/map_bonus.cub
```

### Controls

**Movement:**
- `W` - Move forward
- `S` - Move backward
- `A` - Strafe left
- `D` - Strafe right

**Camera:**
- `←` / `→` - Rotate camera left/right
- `Mouse` (bonus) - Look around

**Doors (bonus):**
- `Space` - Open/close door

**Exit:**
- `ESC` - Close the game
- Click `X` on window - Close the game

## 🏗️ Technical Implementation

### Raycasting Algorithm

The raycasting engine works by:

1. **Casting rays** from the player's position at each screen column
2. **Detecting wall intersections** using DDA (Digital Differential Analysis)
3. **Calculating wall distance** (with fisheye correction)
4. **Projecting walls** to screen height based on distance
5. **Texture mapping** to render textured walls

```
Player Position → Cast Ray → Find Wall Hit → Calculate Distance → Render Column
```

### Key Concepts

**Ray Direction:**
```c
ray_angle = player.angle - (FOV / 2) + (x * FOV / SCREEN_WIDTH);
ray_dir.x = cos(ray_angle);
ray_dir.y = sin(ray_angle);
```

**Distance Calculation:**
- Corrected for fisheye effect using perpendicular distance
- Separate checks for horizontal and vertical grid lines

**Texture Mapping:**
- Calculate hit position on wall
- Map to texture coordinates
- Scale texture height to screen projection

### Minimap (Bonus)

The minimap uses:
- **Bresenham's line algorithm** for ray visualization
- **Cohen-Sutherland clipping** for viewport boundaries
- Real-time player position tracking

### Door System (Bonus)

Animated doors with:
- Open/close animations
- Collision detection
- Timer-based automatic closing
- Teleportation mechanics (special doors)

## 🎨 Example Maps

The project includes several test maps:

- `maps/map.cub` - Basic valid map
- `maps/map_bonus.cub` - Map with doors
- `maps/test_*.cub` - Various edge cases

## 📝 Map Validation

The parser validates:
- Correct file extension (`.cub`)
- All required elements (textures, colors, map)
- Valid RGB values (0-255)
- Closed map (surrounded by walls)
- Single player start position
- No invalid characters

## 🔍 Raycasting Math

### FOV (Field of View)
Default: 60° (π/3 radians)

### Wall Height Projection
```
wall_height = (TILE_SIZE * SCREEN_HEIGHT) / perpendicular_distance
```

### Fisheye Correction
```
perpendicular_distance = distance * cos(ray_angle - player_angle)
```

## ⚙️ Performance

- **Resolution**: 1920x1080 (configurable)
- **Frame rate**: 60+ FPS (depends on map complexity)
- **Ray count**: One ray per screen column

## 🐛 Known Limitations

- No support for multiple floor levels
- Static lighting (no dynamic shadows)
- Simple collision detection (grid-based)
- Limited to orthogonal walls

## 🎓 Learning Outcomes

This project teaches:
- **Raycasting algorithm** and 3D projection
- **Graphics programming** with MiniLibX
- **Trigonometry** in game development
- **Event-driven programming**
- **Map parsing** and validation
- **Performance optimization** for real-time rendering
- **Game loop** and frame timing
- **Team collaboration** in game development

## 👥 Authors

This project was developed in collaboration by:

**Clothilde** (cscache)
- GitHub: [@clothildesc](https://github.com/clothildesc)

**Benjamin** (bsuger)
- GitHub: [@BenjaminSuger](https://github.com/BenjaminSuger)

## 📖 References

- [Wolfenstein 3D (1992)](https://en.wikipedia.org/wiki/Wolfenstein_3D)
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Ray-Casting Tutorial by F. Permadi](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [Original Repository](https://github.com/BenjaminSuger/CUB3D)

## 📄 License

This project is part of the 42 School curriculum.

---

*Built with 🤝 at 42 School*
