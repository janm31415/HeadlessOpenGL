#include <stdio.h>
#include <stdlib.h>
#include "glew/GL/glew.h"
#include "GLFW/glfw3.h"

// Compute shader: writes index*2.0 into buffer
const char* cs_src =
"#version 430 core\n"
"layout(local_size_x = 1) in;\n"
"layout(std430, binding = 0) buffer SSBO {\n"
"    float data[];\n"
"};\n"
"void main() {\n"
"    uint idx = gl_GlobalInvocationID.x;\n"
"    data[idx] = float(idx) * 2.0;\n"
"}\n";

GLuint create_compute_program(const char* src) {
  GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint status = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    char log[512];
    glGetShaderInfoLog(shader, sizeof(log), NULL, log);
    fprintf(stderr, "Compute shader compile error:\n%s\n", log);
    exit(EXIT_FAILURE);
    }

  GLuint prog = glCreateProgram();
  glAttachShader(prog, shader);
  glLinkProgram(prog);

  glGetProgramiv(prog, GL_LINK_STATUS, &status);
  if (!status) {
    char log[512];
    glGetProgramInfoLog(prog, sizeof(log), NULL, log);
    fprintf(stderr, "Program link error:\n%s\n", log);
    exit(EXIT_FAILURE);
    }

  glDeleteShader(shader);
  return prog;
  }

int main(void) {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to init GLFW\n");
    return EXIT_FAILURE;
    }

  // Request OpenGL 4.3+ core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Hidden window

  GLFWwindow* window = glfwCreateWindow(640, 480, "HiddenContext", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return EXIT_FAILURE;
    }

  glfwMakeContextCurrent(window);

  // Init GLEW *after* making context current
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "GLEW init failed: %s\n", glewGetErrorString(err));
    return EXIT_FAILURE;
    }

  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  // Create buffer
  const GLuint num_elements = 16;
  GLuint ssbo;
  glGenBuffers(1, &ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER, num_elements * sizeof(float), NULL, GL_DYNAMIC_COPY);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

  // Create and dispatch compute shader
  GLuint prog = create_compute_program(cs_src);
  glUseProgram(prog);
  glDispatchCompute(num_elements, 1, 1);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

  // Read back
  float* ptr = (float*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
  for (GLuint i = 0; i < num_elements; ++i) {
    printf("data[%u] = %f\n", i, ptr[i]);
    }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  // Cleanup
  glDeleteProgram(prog);
  glDeleteBuffers(1, &ssbo);

  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
  }