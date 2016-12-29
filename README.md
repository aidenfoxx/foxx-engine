# Foxx Engine

A simple OpenGL 3.3 game engine designed with a core C backend and LUA frontend.

## Tasks

The engine is in a constant state of development and the requirements are liable to change.

### Done:
- Model renderer
- Shader management
- Implemented binary model format
- DDS texture loading (DXT1, DXT3, DXT5)
- OBJ model loading
- Binary model editor/converter
- Input management
- Camera controls
- OpenGL math library
- Implement physics
- Assign custom variables to objects

### Todo:
- Implement sound
- Implement LUA frontend
- Add PBR shading
- Add normal texturing

## Bugs:
- Breaks when run from non-root directory.
- Loading non-existent file crashes.
- Make FEM size consistent using uints.
- Remake GLMath and ensure it's working.

## Nomenclature

Model - The 3D structure of an object including vertices, uvs and normals.

ModelBuffer - Model buffer bound to OpenGL.

Texture - Contains 2D texture data.

TextureBuffer - Texture buffer bound to OpenGL.

Object - A wrapper containing everything required to render an object. Created from model buffers, texture buffers and parameters.

Shader - GLSL shader loaded into OpenGL.

Renderer - On execute, renders a number of Objects using various Shaders in OpenGL. Accepts Objects and Shaders.

World - On execute, performs physics and collision calculations to any Objects in the world.