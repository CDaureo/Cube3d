*This project has been created as part of the 42 curriculum by cdaureo- & simgarci.*

# cub3D

## Description
cub3D is a simple 3D raycasting engine project inspired by early 3D games (Wolfenstein 3D).  
The goal is to parse a .cub map file, load textures and colors, and render a realtime 3D view using a raycasting algorithm and miniLibX. The project focuses on correct parsing, map validation, basic textures, and responsive player movement.

## Features (overview)
- Parse .cub configuration files (textures, floor/ceiling colors, map).
- Validate map structure (closed by walls, single player start, allowed characters).
- Load textures and render walls with texture mapping.
- Player movement (W/A/S/D) and rotation (left/right arrow).
- Basic window and input handling via miniLibX.

## Instructions

Prerequisites
- Linux
- gcc / clang
- miniLibX (setup and linked during compilation)
- libft (if used by the project)
- make

Build
1. From project root:
   make

Run
- Correct usage:
  ./cub3D maps/your_map.cub
- Examples:
  ./cub3D maps/example.cub

Notes
- The program validates the input file extension (.cub) and map content. Running with a path missing the .cub extension will produce an error and exit.
- Use valgrind to check for memory leaks:
  valgrind --leak-check=full ./cub3D maps/example.cub

## File format (.cub) summary
- Texture lines:
  - NO ./path/to/north_texture.xpm
  - SO ./path/to/south_texture.xpm
  - WE ./path/to/west_texture.xpm
  - EA ./path/to/east_texture.xpm
- Colors:
  - F 220,100,0   (floor RGB)
  - C 225,30,0    (ceiling RGB)
- Map:
  - A rectangular grid of characters:
  - 1 = wall, 0 = empty, N/S/E/W = player start and orientation, spaces allowed for padding.

## Resources
- miniLibX documentation and examples
- Raycasting tutorials (e.g., Lode Vandevenne's raycasting tutorial)
- C standard library and POSIX manual pages (open, read, close)
- 42 project subject and guidelines

AI usage disclosure
- AI tools were used to assist with:
  - Drafting and improving this README content.
  - Suggesting code refactors and small helper functions during development (parsing helpers, validation routines).
  - Generating unit-test ideas and example validation checks.
- All core logic, final code decisions, and testing were implemented and validated by the project authors. AI output was reviewed and adjusted manually.

## Testing & Validation
- Verify map parsing and validation with both valid and invalid .cub files.
- Test texture file accessibility and correct error messages when resources are missing.
- Check for memory leaks and resource cleanup with valgrind.

## Where to find help
- Inspect the `mandatory_src/` and `includes/` folders for implementation details.
- Open an issue or contact the authors for project-specific questions.

```<!-- filepath: /home/cdaureo-/Cub/README.md -->
*This project has been created as part of the 42 curriculum by cdaureo-. & simgarci*
