cmake_minimum_required(VERSION 3.28)
project(udm)

enable_language(C CXX CUDA)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CUDA_SEPARABLE_COMPILATION  ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(OpenMP REQUIRED)
find_package(OpenCL REQUIRED)


add_library(udm_objs OBJECT udm.c
        device/ocldevice.c
        device/cudevice.c
)

add_library(udm_cuda_objs
        OBJECT
        device/UDMCudaContext.cu
)

target_link_libraries(
        udm_objs
        PUBLIC
        OpenMP::OpenMP_C
        OpenCL::OpenCL
)

target_compile_definitions(
        udm_objs
        PUBLIC
        UDM_TARGET_OMP
)

target_compile_options(
        udm_objs
        PUBLIC
        -save-temps
)

target_compile_options(
        udm_cuda_objs
        PUBLIC
        --save-temps
)



add_library(udm $<TARGET_OBJECTS:udm_objs>
        $<TARGET_OBJECTS:udm_cuda_objs>)



