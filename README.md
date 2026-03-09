# miniRT

> A 42 School project — building a ray tracer from scratch in C using the MiniLibX.

---

## About

`miniRT` is a basic ray tracer written in C. It renders 3D scenes described in `.rt` configuration files, computing ray-object intersections, lighting, shadows, and color shading entirely from scratch — no rendering engine, no shortcuts.

The result is displayed in a window using the **MiniLibX** library, with interactive object movement and camera controls via mouse and keyboard hooks.

---

## Features

- Ray tracing engine written from scratch in C
- Renders **spheres**, **planes**, and **cylinders**
- **Ambient lighting** and **point lights** with diffuse shading
- **Brightness** and **color** per-pixel computation (`bright_pixel.c`, `color_pixel.c`)
- **Scene file parser** — loads `.rt` scene descriptions
- **Interactive controls** — move objects and camera in real time (`object_mov.c`, `hook.c`, `handle_click.c`)
- **MiniLibX** window rendering with keyboard/mouse hooks
- Custom `get_next_line` and `ft_split` for scene parsing
- Error handling and scene validation

---

## Project Structure

```
.
├── object/             # Object-specific intersection logic
├── help_function/      # Vector math and utility helpers
├── main.c / main.h     # Entry point and main structures
├── draw.c              # Ray casting and pixel drawing loop
├── bright_pixel.c      # Lighting / brightness computation
├── color_pixel.c       # Color blending and shading
├── norm.c / norm2.c    # Vector normalisation
├── pars.c → pars7.c    # Scene file parser
├── pars_utils.c        # Parser utilities
├── object_mov.c        # Object and camera movement
├── hook.c              # Keyboard/mouse hooks
├── handle_click.c      # Mouse click handling
├── error.c             # Error management
├── get_next_line.c     # GNL for reading scene files
├── ft_split.c          # String splitting utility
├── sphere.rt           # Example sphere scene
├── plane.rt            # Example plane scene
├── cyl.rt              # Example cylinder scene
└── Makefile
```

---

## Scene File Format (`.rt`)

Scenes are described in `.rt` files. Each element is on its own line:

```
A  0.2                     255,255,255    # Ambient: ratio, color
C  0,0,-5    0,0,1    70                 # Camera: position, direction, FOV
L  -2,5,0    1.0      255,255,255        # Light: position, brightness, color

sp 0,0,3     2        255,0,0            # Sphere: center, diameter, color
pl 0,-1,0    0,1,0    0,255,0            # Plane: point, normal, color
cy 0,0,5     0,1,0  1  3  0,0,255       # Cylinder: center, axis, diameter, height, color
```

### Supported elements

| Identifier | Object         |
|------------|----------------|
| `A`        | Ambient light  |
| `C`        | Camera         |
| `L`        | Point light    |
| `sp`       | Sphere         |
| `pl`       | Plane          |
| `cy`       | Cylinder       |

---

## Usage

### Requirements

- **OS:** Linux or macOS
- **MiniLibX** installed
- **gcc** / **make**

### Build

```bash
make
```

### Run

```bash
./miniRT sphere.rt
./miniRT plane.rt
./miniRT cyl.rt
```

### Controls

| Key / Action     | Effect                   |
|------------------|--------------------------|
| `ESC`            | Close the window         |
| Arrow keys       | Move the selected object |
| Mouse click      | Select an object         |
| `W` `A` `S` `D` | Move camera              |

---

## Author

**CarsonJo** — [github.com/CarsonJo](https://github.com/CarsonJo)
