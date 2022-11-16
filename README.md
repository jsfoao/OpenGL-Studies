# OpenGL Studies
![Demo](/docs/demo.gif  "Demo")

## Highlights
- OpenGL Abstraction
- Directional and point lighting
- Input system

## OpenGL Abstraction
Based on this [repo](https://github.com/Pikachuxxxx/OpenGL-Abstractions), I created my own OpenGL abstraction. This implementation is simple enough for testing OpenGL features on a small scale rendering engine like this one.

The following example shows how shaders, textures and models can be loaded and added to the scene.
```cpp
// Loading shader
Shader shader("src\\shaders\\lit.vert", "src\\shaders\\lit.frag");
// Loading texture
Texture texture("container2.png", "res", TEXTURE_DIFFUSE);
// Loading model
Model ourModel("res\\models\\teapot.obj");
// Binding texture to model
ourModel.AddTexture(texture);
```

## Lighting
Implementation of specular, diffuse and ambient shading.
![Light Sources](/docs/lightsources.gif  "Light Sources")
![Light Sources](/docs/coloredlightsources.gif  "Light Sources")

## Input System
This simple input implementation is based on [TheCherno's Sparky Engine input system](https://github.com/TheCherno/Sparky).

Example of how input system can be used to navigate camera.
![Camera Input](/docs/input.gif  "Camera Input")
```cpp
// Using input system to move camera forward
if (input->GetKeyDown(GLFW_KEY_W))
{
	camPos += camSpeed * camForward * deltaTime;
}
```
## Dependencies
 * [glfw](https://github.com/glfw/glfw) : A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input.
 * [glew](http://glew.sourceforge.net) : The OpenGL Extension Wrangler Library.
 * [glm](https://github.com/g-truc/glm) : OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
* [Assimp](https://www.assimp.org) : The Open Asset Import Library (short name: Assimp) is a portable Open-Source library to import various well-known 3D model formats in a uniform manner.
* [imgui](http://glew.sourceforge.net) : Graphical user interface library.

## Sources
- [Learn OpenGL](https://learnopengl.com/)
- [OpenGL Abstractions](https://github.com/Pikachuxxxx/OpenGL-Abstractions)
- [TheCherno's Sparky](https://github.com/TheCherno/Sparky)
