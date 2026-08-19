include(FetchContent)

FetchContent_Declare(
    rangetap
    GIT_REPOSITORY https://github.com/dmishura/RangeTap.git
    GIT_TAG        main
)

set(RNTP_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(rangetap)