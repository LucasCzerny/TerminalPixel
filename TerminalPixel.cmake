add_executable("TerminalPixel"
    "src/camera/camera.cpp"
    "src/camera/camera.hpp"
    "src/light/light.cpp"
    "src/light/light.hpp"
  "src/main.cpp"
      "src/platform/linux/linux.cpp"
    "src/platform/terminal_util.hpp"
    "src/ray/ray.hpp"
    "src/renderer/color.cpp"
    "src/renderer/color.hpp"
    "src/renderer/renderer.cpp"
    "src/renderer/renderer.hpp"
    "src/shapes/box.cpp"
    "src/shapes/box.hpp"
    "src/shapes/shape.hpp"
    "src/shapes/sphere.cpp"
    "src/shapes/sphere.hpp"
    "src/terminal/terminal.cpp"
    "src/terminal/terminal.hpp"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("TerminalPixel" PROPERTIES
    OUTPUT_NAME "TerminalPixel"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/TerminalPixel/bin/Debug"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/TerminalPixel/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/TerminalPixel/bin/Debug"
  )
endif()
target_include_directories("TerminalPixel" PRIVATE
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/TerminalPixel/src>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/TerminalPixel/packages/glm/include>
)
target_compile_definitions("TerminalPixel" PRIVATE
  $<$<CONFIG:Debug>:TPIXEL_DEBUG>
)
target_link_directories("TerminalPixel" PRIVATE
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/TerminalPixel/packages/glm/lib>
)
target_link_libraries("TerminalPixel"
  $<$<CONFIG:Debug>:libglm.a>
)
target_compile_options("TerminalPixel" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("TerminalPixel" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("TerminalPixel" PROPERTIES
    OUTPUT_NAME "TerminalPixel"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/TerminalPixel/bin/Release"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/TerminalPixel/bin/Release"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/TerminalPixel/bin/Release"
  )
endif()
target_include_directories("TerminalPixel" PRIVATE
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/TerminalPixel/src>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/TerminalPixel/packages/glm/include>
)
target_compile_definitions("TerminalPixel" PRIVATE
  $<$<CONFIG:Release>:TPIXEL_RELEASE>
)
target_link_directories("TerminalPixel" PRIVATE
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/TerminalPixel/packages/glm/lib>
)
target_link_libraries("TerminalPixel"
  $<$<CONFIG:Release>:libglm.a>
)
target_compile_options("TerminalPixel" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("TerminalPixel" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()