# MiniRT

MiniRT is a minimalist ray tracer written in C. It renders simple 3D scenes composed of spheres, planes, and cylinders while implementing the fundamental concepts of ray tracing, including ray generation, object intersection, lighting, shading, and camera manipulation.

---

## Overview

This project introduces the core principles of ray tracing:

- **Ray Generation** – Casting rays from a virtual camera through an image plane into the scene.
- **Object Intersection** – Detecting intersections between rays and geometric primitives such as spheres, planes, and cylinders.
- **Lighting and Shading** – Computing pixel colors based on light sources, material properties, surface normals, and shadows.
- **Camera Controls** – Navigating and rotating the camera within the scene in real time.

---

## Dependencies

MiniRT relies on the following libraries:

### MiniLibX (MLX)
A lightweight graphics library used for:

- Creating application windows
- Handling keyboard events
- Rendering pixels to the screen

### libft
A custom utility library providing:

- String manipulation functions
- Memory management utilities
- Linked list implementations
- General helper functions

### Math Library (`libm`)
The standard C math library used for operations such as:

- `sqrt()`
- `pow()`
- `cos()`
- `sin()`

---

## Project Structure

```text
.
├── src/
│   ├── main.c
│   ├── render.c
│   ├── camera_*.c
│   ├── op_ray_*.c
│   ├── op_obj_*.c
│   ├── light_shd_*.c
│   ├── parse_*.c
│   ├── vec_*.c
│   ├── matrix_*.c
│   ├── math_utils.c
│   ├── control.c
│   ├── move_cm.c
│   └── test_utils_*.c
│
├── include/
│   ├── minirt.h
│   └── structs.h
│
├── subject/
│   └── subject.pdf
│
└── Makefile
```

### Source Directory (`src/`)

| File(s) | Description |
|----------|-------------|
| `main.c` | Program entry point |
| `render.c` | Main ray tracing loop |
| `camera_*.c` | Camera setup and manipulation |
| `op_ray_*.c` | Ray generation and intersection calculations |
| `op_obj_*.c` | Object property manipulation |
| `light_shd_*.c` | Lighting and shading calculations |
| `parse_*.c` | Scene file parsing |
| `vec_*.c`, `matrix_*.c`, `math_utils.c` | Mathematical operations and utilities |
| `control.c`, `move_cm.c` | Keyboard input and camera movement |
| `test_utils_*.c` | Debugging and utility functions |

### Include Directory (`include/`)

| File | Description |
|--------|-------------|
| `minirt.h` | Main header containing declarations and prototypes |
| `structs.h` | Definitions of project data structures |

### Other Files

| File | Description |
|--------|-------------|
| `subject/subject.pdf` | Project specification |
| `Makefile` | Build configuration |

---

## Compilation

Build the project from the root directory:

```bash
make
```

This compiles all source files and generates the executable:

```bash
miniRT
```

### Available Make Targets

```bash
make clean
```

Removes object files (`.o`).

```bash
make fclean
```

Removes object files and the executable.

```bash
make re
```

Performs a full rebuild (`fclean` followed by `make`).

---

## Usage

Run MiniRT with a scene description file:

```bash
./miniRT path/to/scene.rt
```

Example:

```bash
./miniRT scenes/example.rt
```

---

## Scene File Format (`.rt`)

A scene file describes the objects, camera, and lighting present in the scene. Each line begins with an identifier that specifies the type of element being defined.

### Supported Identifiers

| Identifier | Description |
|------------|-------------|
| `A` | Ambient light |
| `C` | Camera |
| `L` | Point light source |
| `sp` | Sphere |
| `pl` | Plane |
| `cy` | Cylinder |

---

## Example Scene

```text
A 0.2 255,255,255
C -50.0,0,20 0,0,1 70
L -40.0,50.0,0.0 0.6 10,0,255

sp 0.0,0.0,20.0 20.0 255,0,0
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
```

---

## Controls

After the scene is rendered, the camera can be controlled using the keyboard.

### Movement

| Key | Action |
|------|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `Q` | Move up |
| `E` | Move down |

### Rotation

| Key | Action |
|------|--------|
| `↑` | Look up |
| `↓` | Look down |
| `←` | Rotate left |
| `→` | Rotate right |

### Exit

| Key | Action |
|------|--------|
| `ESC` | Close the application |

---

## Learning Objectives

This project provides practical experience with:

- Computer graphics fundamentals
- Ray tracing algorithms
- 3D vector and matrix mathematics
- Geometric intersection calculations
- Lighting and shading models
- Event-driven graphics programming
- Scene parsing and data management in C