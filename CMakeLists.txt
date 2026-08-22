cmake_minimum_required(VERSION 3.21)

project(
        GAL
        VERSION 0.1.0
        LANGUAGES C CXX
)

option(GAL_BUILD_EXAMPLES "Build GAL examples" ON)
option(GAL_BUILD_DEV "Build GAL development tests" OFF)

include(FetchContent)

find_package(glm QUIET)
if(NOT glm_FOUND)
    message(STATUS "Fetching GLM...")
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.3
    )
    FetchContent_MakeAvailable(glm)
endif()

find_package(glfw3 QUIET)
if(NOT glm_FOUND)
    message(STATUS "Fetching GLM...")
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.5.1
    )
    FetchContent_MakeAvailable(glfw)
endif()

add_library(glad STATIC third-party/glad/src/gl.c)

target_include_directories(glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/glad/include>
        $<INSTALL_INTERFACE:include>
)

add_library(GAL INTERFACE
        include/GAL/gal.hpp
        include/GAL/types.hpp
        include/GAL/detail/UniqueHandle.hpp
        include/GAL/core/Window.hpp
        include/GAL/detail/ResourceRegistry.hpp
        include/GAL/detail/logging.hpp
        include/GAL/core/core.hpp
        include/GAL/detail/detail.hpp
        include/GAL/core/init.hpp
        include/GAL/core/enums.hpp
        include/GAL/core/GALException.hpp
        include/GAL/debug/debug.hpp
        include/GAL/core/keyboard.hpp
        include/GAL/graphics/graphics.hpp
        include/GAL/graphics/Program.hpp
        include/GAL/graphics/Shader.hpp
        include/GAL/system/system.hpp
        include/GAL/system/time.hpp
        include/GAL/graphics/Buffer.hpp
        include/GAL/glmIncludes.hpp
        include/GAL/graphics/VertexArray.hpp
        include/GAL/system/GLParams.hpp
        include/GAL/graphics/Texture.hpp
        include/GAL/debug/callbacks.hpp
)

target_link_libraries(GAL INTERFACE
        glm::glm
        glfw
        glad
)

add_library(GAL::GAL ALIAS GAL)

target_include_directories(GAL INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(GAL INTERFACE cxx_std_17)

function(copyAssets target)
    string(RANDOM LENGTH 64 unique_target)
    
    add_custom_target(${unique_target}
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/copy_assets.cmake ${CMAKE_CURRENT_LIST_DIR}/assets
    )

    add_dependencies(${target} ${unique_target})
endfunction()

if (GAL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (GAL_BUILD_DEV)
    add_subdirectory(dev)
endif()

# TODO: Installation