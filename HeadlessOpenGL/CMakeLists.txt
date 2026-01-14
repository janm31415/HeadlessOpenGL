if (WIN32)
  set(OPENGL_LIBRARIES opengl32.lib CACHE FILEPATH "opengl lib file")
  set(GLX_LIBRARIES "")
endif (WIN32)

if (UNIX)
  set(OPENGL_LIBRARIES "/usr/lib/x86_64-linux-gnu/libOpenGL.so.0.0.0" CACHE FILEPATH "opengl lib file")
  set(GLX_LIBRARIES "/usr/lib/x86_64-linux-gnu/libGLX.so" CACHE FILEPATH "glx lib files")
endif (UNIX)

set(HDRS
)
	
set(SRCS
glew.cpp
main.cpp
)

if (WIN32)
set(CMAKE_C_FLAGS_DEBUG "/W4 /MP /GF /RTCu /Od /MDd /Zi")
set(CMAKE_C_FLAGS_RELEASE "/W4 /MP /GF /O2 /Ob2 /Oi /Ot /MD /Zi /DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "/W4 /MP /GF /RTCu /Od /MDd /Zi")
set(CMAKE_CXX_FLAGS_RELEASE "/W4 /MP /GF /O2 /Ob2 /Oi /Ot /MD /Zi /DNDEBUG")
else(WIN32)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
endif(WIN32)

add_definitions(-DMEMORY_LEAK_TRACKING)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_executable(HeadlessOpenGL ${HDRS} ${SRCS})
source_group("Header Files" FILES ${hdrs})
source_group("Source Files" FILES ${srcs})

target_include_directories(HeadlessOpenGL
    PUBLIC  
    ${CMAKE_CURRENT_SOURCE_DIR}/../glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include
    )	
	
target_link_libraries(HeadlessOpenGL
    PRIVATE
    ${OPENGL_LIBRARIES}
    ${GLX_LIBRARIES}
    glfw
    )    
