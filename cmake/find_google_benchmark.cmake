include(FetchContent)

# Google Benchmark 1.8.3
# 2023 August 31 (latest as of 2024 January 29)
FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG 344117638c8ff7e239044fd0fa7085839fc03021
    FIND_PACKAGE_ARGS NAMES benchmark
)

FetchContent_MakeAvailable(google_benchmark)
