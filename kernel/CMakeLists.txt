file(GLOB_RECURSE ARMADILLO_KERNEL_SOURCES *.c)
file(GLOB_RECURSE ARMADILLO_ASM_SOURCES *.s)

add_executable(armadillo ${ARMADILLO_ASM_SOURCES} ${ARMADILLO_KERNEL_SOURCES})

# libgcc is needed for some division
# intrinsics for ARM
target_link_libraries(armadillo gcc)
