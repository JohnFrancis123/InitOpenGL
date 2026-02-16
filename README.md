# InitOpenGL

A C++ OpenGL graphics application featuring advanced rendering techniques, camera systems, and interactive 3D scenes.

## Features

- **Advanced Rendering**: Support for diffuse lighting, specular highlights, and custom shaders
- **Multiple Scene Modes**: 
  - Water Scene with wave simulation
  - Space Scene with skybox rendering
  - Transform mode for object manipulation
  - Light positioning mode
- **Camera System**: Flexible camera controls for scene navigation
- **Post-Processing Effects**: Real-time post-processing pipeline
- **Font Rendering**: Text rendering with FreeType integration
- **Mesh Loading**: Support for 3D model loading and rendering
- **Skybox Rendering**: Environment mapping with custom skyboxes

## Prerequisites

- **Visual Studio 2017 or later** (Windows) - includes C++11 compatible compiler
- **CMake** (optional, for building external libraries)

## Dependencies

All required dependencies are included in the `External` folder:

- **GLFW 3.3.4** - Window and input handling
- **GLEW 2.1.0** - OpenGL extension loading
- **GLM** - OpenGL Mathematics library
- **FreeType 2.10.4** - Font rendering
- **STB** - Image loading
- **OBJ Loader** - 3D model loading

## Building

### Windows (Visual Studio)

1. Clone the repository:
   ```bash
   git clone https://github.com/JohnFrancis123/InitOpenGL.git
   cd InitOpenGL
   ```

2. Open `InitOpenGL.sln` in Visual Studio

3. Select your target configuration:
   - Debug or Release
   - x86 or x64

4. Build the solution (F7 or Build > Build Solution)

5. Run the application (F5 or Debug > Start Debugging)

## Project Structure

```
InitOpenGL/
├── Assets/              # Game assets
│   ├── Fonts/          # Font files
│   ├── Models/         # 3D models
│   └── Textures/       # Texture files
├── External/           # Third-party libraries
│   ├── freetype-2.10.4/
│   ├── glew-2.1.0/
│   ├── glfw-3.3.4/
│   ├── glm/
│   ├── obj_loader/
│   └── stb/
└── OpenGL/             # Source code
    ├── Camera.cpp/h    # Camera implementation
    ├── GameController.cpp/h  # Main game logic
    ├── Mesh.cpp/h      # Mesh rendering
    ├── Shader.cpp/h    # Shader management
    ├── Skybox.cpp/h    # Skybox rendering
    ├── Texture.cpp/h   # Texture loading
    ├── Fonts.cpp/h     # Text rendering
    ├── PostProcessor.cpp/h  # Post-processing
    ├── WindowController.cpp/h  # Window management
    └── main.cpp        # Application entry point
```

## Shaders

The application includes several shader programs:

- **Color Shader**: Basic color rendering
- **Diffuse Shader**: Diffuse lighting calculations
- **Skybox Shader**: Environment mapping
- **Font Shader**: Text rendering
- **Post-Processor Shader**: Screen-space effects

## Controls

The application supports mouse-based interactions for:
- Camera movement and rotation
- Object transformation (translation, rotation, scaling)
- Light positioning
- Scene navigation

## Configuration

The application uses a singleton pattern for core controllers:
- `GameController` - Main game loop and state management
- `WindowController` - Window creation and management

Resolution settings can be configured through the `Resolution.h` header.

## License

This project is available for educational purposes.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Author

John Francis

## Acknowledgments

- GLFW team for the windowing library
- GLEW team for OpenGL extension loading
- GLM team for the mathematics library
- FreeType for font rendering support
