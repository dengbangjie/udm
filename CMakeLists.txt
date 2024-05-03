cmake_minimum_required(VERSION 3.28)
project(udm)

enable_language(C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(UDM_BUILD_CUDA OFF CACHE BOOL "Enable cuda devices")
set(UDM_BUILD_OPENCL OFF CACHE BOOL "Enable opencl devices")

if (UDM_BUILD_CUDA)
    enable_language(CUDA)
    set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)
    set(CMAKE_CUDA_ARCHITECTURES "all-major")
endif ()


find_package(OpenMP REQUIRED)

if (UDM_BUILD_CUDA)
    find_package(OpenCL REQUIRED)
endif ()


add_library(udm_objs OBJECT
        udm.c
        # device
        device/ocldevice.c
        device/cudevice.c
        udm_device.c
        # topology
        topo/SMesh.c
)


target_link_libraries(
        udm_objs
        PUBLIC
        OpenMP::OpenMP_C
)


if (UDM_BUILD_OPENCL)
    target_link_libraries(
            udm_objs
            PUBLIC
            OpenCL::OpenCL
    )

endif ()


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

if (UDM_BUILD_CUDA)

    add_library(udm_cuda_objs
            OBJECT
            device/UDMCudaContext.cu
    )

    target_compile_options(
            udm_cuda_objs
            PUBLIC
            --save-temps
    )

endif ()


list(APPEND UDM_OBJECTS $<TARGET_OBJECTS:udm_objs>)

if (UDM_BUILD_CUDA)

    list(APPEND UDM_OBJECTS $<TARGET_OBJECTS:udm_cuda_objs>)

endif ()

add_library(udm
        SHARED
        ${UDM_OBJECTS})


set_target_properties(
        udm
        PROPERTIES
        LINKER_LANGUAGE "C"
)


