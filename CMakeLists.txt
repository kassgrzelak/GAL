cmake_minimum_required(VERSION 3.21)
project(GAL VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

# ========================
# Options
# ========================
option(GAL_BUILD_EXAMPLES "Build GAL examples" ON)
option(GAL_FETCH_DEPENDENCIES "Fetch dependencies if not found" ON)
option(GAL_BUILD_DEV "Build GAL development tests" OFF)

# ========================
# Dependencies
# ========================

# ---- GLFW ----
find_package(glfw3 CONFIG QUIET)
if(NOT glfw3_FOUND AND GAL_FETCH_DEPENDENCIES)
    message(STATUS "Fetching GLFW...")
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw)
endif()

# Normalize GLFW target
if(TARGET glfw)
    set(GAL_GLFW_TARGET glfw)
elseif(TARGET glfw3)
    set(GAL_GLFW_TARGET glfw3)
else()
    message(FATAL_ERROR "GLFW not found or fetched.")
endif()

# ---- GLM ----
find_package(glm CONFIG QUIET)
if(NOT glm_FOUND AND GAL_FETCH_DEPENDENCIES)
    message(STATUS "Fetching GLM...")
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif()

# Normalize GLM target
if(TARGET glm::glm)
    set(GAL_GLM_TARGET glm::glm)
elseif(TARGET glm)
    set(GAL_GLM_TARGET glm)
else()
    message(FATAL_ERROR "GLM not found or fetched.")
endif()

# ---- GLAD (vendored) ----
add_library(glad STATIC third-party/glad/src/gl.c)
add_library(glad::glad ALIAS glad)

target_include_directories(glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/glad/include>
        $<INSTALL_INTERFACE:include>
)

# ========================
# GAL Library
# ========================
add_library(GAL INTERFACE
        include/GAL/gal.hpp
        include/GAL/types.hpp
        include/GAL/config.hpp
        include/GAL/detail/UniqueHandle.hpp
        include/GAL/core/Window.hpp
        include/GAL/detail/ResourceRegistry.hpp
        include/GAL/detail/logging.hpp
        include/GAL/core/core.hpp
        include/GAL/detail/detail.hpp
        include/GAL/core/init.hpp
        include/GAL/core/enums.hpp
        include/GAL/core/GALException.hpp)
add_library(GAL::GAL ALIAS GAL)

target_compile_features(GAL INTERFACE cxx_std_17)

target_include_directories(GAL INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(GAL INTERFACE
        ${GAL_GLFW_TARGET}
        ${GAL_GLM_TARGET}
        glad::glad
)

# ========================
# Examples (optional)
# ========================
if(GAL_BUILD_EXAMPLES)
    add_executable(GAL_example examples/example.cpp)
    target_link_libraries(GAL_example PRIVATE GAL::GAL)
endif()

# ========================
# Development tests
# ========================
if(GAL_BUILD_DEV)
    add_subdirectory(dev)
    add_subdirectory(unit-tests)
endif()

# ========================
# Installation
# ========================
include(GNUInstallDirs)

install(TARGETS GAL glad
        EXPORT GALTargets
)

install(
        DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
        EXPORT GALTargets
        FILE GALTargets.cmake
        NAMESPACE GAL::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GAL
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/GALConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/GALConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/GALConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GAL
)

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/GALConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/GALConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GAL
)
