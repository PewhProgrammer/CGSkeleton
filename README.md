# CGSkeleton

A CPU raytracer written in C++ for the Computer Graphics (CG1) course at Saarland University. Started from the course-provided skeleton, then extended assignment by assignment into a full renderer: acceleration structures, multiple camera models, lights, materials, procedural textures, and a final scene ("rc", the course's capstone render).

> **Status:** Archived. Coursework completed for its assignments and no longer actively developed.

## Features

- **Geometry**: spheres, triangles, quads, discs, axis-aligned boxes, infinite planes, instancing, OBJ loading (`rt/loaders/obj.cpp`)
- **Acceleration**: BVH and a k-d tree (`rt/groups/`) for fast ray/scene intersection
- **Cameras**: perspective, orthographic, fisheye, depth-of-field perspective, environment (`rt/cameras/`)
- **Integrators**: ray casting, distributed ray casting, iterative and recursive raytracing (`rt/integrators/`)
- **Lights**: point, directional, spot, area, ambient, projective (`rt/lights/`)
- **Materials**: Lambertian, mirror, fuzzy mirror, glass, flat, combine/blend (`rt/materials/`)
- **Textures & mapping**: constant, checkerboard, Perlin noise, image textures, plus planar/cylindrical/spherical/environment coordinate mappers (`rt/textures/`, `rt/coordmappers/`)
- **Assignments** (`main/a_*.cpp`): standalone scenes for cameras, solids, indexing, instancing, lighting, materials, distributed raytracing, textures, smooth shading, bump mapping, and Julia set fractals

## Project structure

```
core/     Math and image primitives (vector, matrix, color, image I/O)
rt/       The raytracer library: cameras, groups, lights, materials, textures, integrators
main/     Assignment entry points (a_*.cpp) and the final scene (rc.cpp)
models/   OBJ/material assets used by the assignments and final scene
```

## Building

This project targets **Windows with Visual Studio** (`CG1raytracer.sln`), and has a hard dependency on `<windows.h>` in `rt/guiConsole.h` for the live preview window. Open the solution in Visual Studio and build/run.

A `Makefile` (g++, requires `libpng`) is also included from the course's Linux/CIP lab setup, but it targets the same Windows-oriented headers and include paths (backslash-separated `#include` paths throughout, which MSVC accepts but GCC/Clang do not), so it isn't expected to build as-is outside of MSVC.

Running `rc()` (the final scene, see `main/main.cpp`) renders at up to 400 samples per pixel; per the code's own comment, roughly 200 samples takes about 3.5 hours on course-era hardware. No prebuilt renders are checked into this repo.

## Related

The raytracer core here (`rt/`, `core/`) is the basis later reused and adapted in [Scansify](https://github.com/PewhProgrammer/Scansify)'s 3D annotation/mouse-picking pipeline.

## Author

Ba Thinh Tran — [PewhProgrammer](https://github.com/PewhProgrammer)
