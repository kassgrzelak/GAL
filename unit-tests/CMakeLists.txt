include(FetchContent)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(catch2)

add_executable(GAL_dev_tests
        main.cpp
        test_RAII.cpp
)

target_include_directories(GAL_dev_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(GAL_dev_tests PRIVATE GAL::GAL Catch2::Catch2WithMain)

enable_testing()
add_test(NAME GAL_dev_tests COMMAND GAL_dev_tests)
