# HeadlessOpenGL

**HeadlessOpenGL** is a minimal C/C++ example showing how to create and use an OpenGL context *without* displaying a window.  
It uses [GLFW](https://www.glfw.org/) for context creation and [GLEW](http://glew.sourceforge.net/) for OpenGL function loading.

## Purpose

The goal of this project is to demonstrate how to:
- Create a modern OpenGL (4.3+) **core profile** context in a *headless* manner.
- Dispatch **compute shaders** or perform **offscreen GPU work** without any on-screen rendering.
- Work cross-platform (Windows / Linux) with minimal dependencies.

This is useful for:
- GPU-accelerated computation via OpenGL compute shaders.
- Automated rendering pipelines that save images to disk.
- Server-side OpenGL workloads without an attached display.

---

## How It Works

OpenGL requires a valid context to run, even for compute work.  
GLFW is used here to create a small hidden window (never shown) with an OpenGL context.  
GLEW loads all the modern OpenGL functions and constants so you can use OpenGL 3.x/4.x APIs without worrying about platform-specific loading code.

The example:
1. Initializes GLFW and requests OpenGL 4.3 core profile.
2. Creates a hidden window (`GLFW_VISIBLE = GLFW_FALSE`).
3. Loads all OpenGL functions via GLEW.
4. Sets up a **Shader Storage Buffer Object (SSBO)**.
5. Compiles and runs a **compute shader** that writes values into the SSBO.
6. Reads back results on the CPU and prints them.
7. Cleans up and exits.

---

## Example Output

When running the executable, you might see:

```bash
OpenGL version: 4.3.0 NVIDIA 581.42
Renderer: NVIDIA T1000/PCIe/SSE2
Vendor: NVIDIA Corporation
data[0] = 0.000000
data[1] = 2.000000
data[2] = 4.000000
...
data[15] = 30.000000
```

## Building with CMake



### **Requirements**

- CMake 3.10+  

- OpenGL 4.3+ capable GPU and drivers  

- [GLFW](https://www.glfw.org/) is provided as a submodule 

- [GLEW](http://glew.sourceforge.net/) is provided as code  



---



### **Steps**



```bash

# 1. Clone the repository

git clone https://github.com/yourusername/HeadlessOpenGL.git

cd HeadlessOpenGL



# 2. Create a build directory

mkdir build && cd build



# 3. Configure the project with CMake

cmake ..



# 4. Build the project

cmake --build .



# 5. Run the executable


./HeadlessOpenGL
```

