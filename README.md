# WFC Biome Generator

![WFC Biome Generator demo](gif_example.gif)

WFC Biome Generator is a C++/SFML terrain generator that builds a colored biome map using a Wave Function Collapse-style algorithm. Each tile starts with every biome as a possibility, then the program repeatedly chooses a low-entropy tile, collapses it into one biome, and propagates the biome adjacency rules to neighboring tiles until the whole map is filled.

The result is a procedural world map where terrain transitions are constrained: deep ocean connects to ocean, water moves toward coast and beach, plains can lead into forest, desert, or mountains, and snow appears around mountains.

## Features

- Real-time animated generation on a 48x48 tile map
- Seeded random generation for repeatable maps
- Regenerate and new-seed controls
- Adjustable generation speed
- SFML rendering with a simple sidebar UI
- CMake build setup with SFML 3 support

## How It Works

The generator is built around three main pieces:

- `Cell`: stores a tile's grid position, collapsed biome, remaining possible biomes, and cached entropy.
- `Map`: owns the grid, random seed, biome rules, entropy queue, collapse logic, and propagation logic.
- `Renderer`: converts collapsed biomes into colors and draws the grid with SFML.

Generation starts by resetting every cell to the full biome option mask. On each step, the map picks the uncollapsed cell with the lowest entropy, randomly chooses one of its remaining biome options, and collapses the cell to that biome. The collapsed cell is then pushed through a propagation queue so neighboring cells remove any biome options that are not allowed next to the source cell. This process continues until no uncollapsed cells remain.

Biome compatibility is defined in `Map::buildRules()` using bitmasks. Those rules act like a small DFA-style transition system: a neighbor is valid only if its biome appears in the allowed-neighbor mask for the current biome.

## Controls

- `Regenerate`: rebuilds the map with the current seed
- `New Seed`: creates a new random seed and starts over
- `Slower` / `Faster`: changes how many cells are collapsed per frame
- `Space`: generate with a new seed
- `R`: regenerate with the current seed
- `Escape`: close the app

## Build and Run

Requirements:

- CMake 3.28 or newer
- A C++17 compiler
- SFML 3

If SFML is not already installed, the CMake project can fetch SFML 3.0.2 automatically.

```sh
cmake -B build
cmake --build build --config Release
```

Run the generated executable from the build output directory:

```sh
./build/bin/WFCBiomeGenerator
```

On multi-config generators such as Visual Studio, the executable may be under a configuration folder such as `build/bin/Release`.
