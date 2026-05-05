cmake_minimum_required(VERSION 3.10)
project(TOPSIS)

set(CMAKE_CXX_STANDARD 20)

# Configuración de depuración por defecto
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Opciones de build type
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

# Flags de compilación para depuración
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g -O2 -DNDEBUG")

# Crear la librería interna TOPSIS
add_library(topsis_lib STATIC TOPSIS.cpp TOPSIS.hpp)
target_include_directories(topsis_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Configuración específica para la librería en modo Debug
target_compile_options(topsis_lib PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
    $<$<CONFIG:RelWithDebInfo>:-g -O2 -DNDEBUG>
)

# Crear el ejecutable principal
add_executable(TOPSIS main.cpp)

# Configuración específica para el ejecutable en modo Debug
target_compile_options(TOPSIS PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
    $<$<CONFIG:RelWithDebInfo>:-g -O2 -DNDEBUG>
)

# Vincular la librería al ejecutable
target_link_libraries(TOPSIS PRIVATE topsis_lib)
