# Cub3D (125/100)

**Cub3D** is a project at 42 School that involves creating a simple 3D game engine using the Raycasting technique. The goal is to build a basic 3D game that renders a textured maze environment and allows the player to navigate through it.

## Features
- Custom implementation of a 3D game engine using Raycasting.
- Supports rendering textured walls, sprites, and a player's perspective view.
- Supports rendering animated sprites. (bonus)
- Integration with the MiniLibX graphics library for real-time rendering.
- Supports player movement and rotation with keyboard. Supports player rotation with mouse as well. (bonus)
- Integrated minimap. (bonus)
- Supports collision with walls, and interaction with doors. (bonus)

## Usage
1. Clone the repository:
   <pre>
   git clone https://github.com/Thawnder/cub3d.git
   </pre>
2. Compile the Cub3D program:
   <pre>
   make
   </pre>
3. Run the Cub3D program with a map file as an argument:
   <pre>
   ./cub3d map.cub
   </pre>

## Example
<pre>
$ ./cub3d map.cub

<p align="center"> <img src="Cub3D.gif" alt="animated" /> </p>
