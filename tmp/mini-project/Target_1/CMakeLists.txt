# CMSIS Build CMakeLists generated on 2023-12-03T17:55:19

cmake_minimum_required(VERSION 3.22)

# Target options

set(TARGET mini-project)
set(CPU Cortex-M4)
set(PRJ_DIR "a:/Work/Projects/mbed/mini-project-TM4C123")
set(OUT_DIR "A:/Work/Projects/mbed/mini-project-TM4C123/out/mini-project/Target_1")
set(INT_DIR "A:/Work/Projects/mbed/mini-project-TM4C123/tmp/mini-project/Target_1")
set(FPU SP_FPU)
set(SECURE Non-secure)
set(BYTE_ORDER Little-endian)
set(OPTIMIZE none)
set(DEBUG on)
set(AS_FLAGS_GLOBAL "-masm=auto")
set(CC_FLAGS_GLOBAL "-std=c90 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(CXX_FLAGS_GLOBAL "-xc++ -std=c++03 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wno-packed -Wno-missing-variable-declarations -Wno-missing-prototypes -Wno-missing-noreturn -Wno-sign-conversion -Wno-nonportable-include-path -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(LD_FLAGS_GLOBAL "--map --load_addr_map_info --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --strict --summary_stderr --info summarysizes")
set(LD_SCRIPT "a:/Work/Projects/mbed/mini-project-TM4C123/RTE/Device/TM4C123GH6PM/ac6_linker_script.sct.src")
set(LD_REGIONS "a:/Work/Projects/mbed/mini-project-TM4C123/RTE/Device/TM4C123GH6PM/regions_TM4C123GH6PM.h")
set(LD_SCRIPT_PP "A:/Work/Projects/mbed/mini-project-TM4C123/tmp/mini-project/Target_1/ac6_linker_script.sct")

set(DEFINES
  TM4C123GH6PM
  _RTE_
)

set(INC_PATHS
  "a:/Work/Projects/mbed/mini-project-TM4C123/RTE/_Target_1"
  "C:/Users/harit/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
  "C:/Users/harit/AppData/Local/Arm/Packs/Keil/TM4C_DFP/1.1.0/Device/Include/TM4C123"
  "a:/Work/Projects/mbed/mini-project-TM4C123"
)

set(AS_ARM_SRC_FILES
  "a:/Work/Projects/mbed/mini-project-TM4C123/RTE/Device/TM4C123GH6PM/startup_TM4C123.s"
)

set(CC_SRC_FILES
  "a:/Work/Projects/mbed/mini-project-TM4C123/RTE/Device/TM4C123GH6PM/system_TM4C123.c"
  "a:/Work/Projects/mbed/mini-project-TM4C123/clock.c"
  "a:/Work/Projects/mbed/mini-project-TM4C123/keypad.c"
  "a:/Work/Projects/mbed/mini-project-TM4C123/lcd.c"
  "a:/Work/Projects/mbed/mini-project-TM4C123/main.c"
  "a:/Work/Projects/mbed/mini-project-TM4C123/port_init.c"
)

set(LIB_FILES
  "a:/Work/Projects/mbed/mini-project-TM4C123/texas.o"
)

# Toolchain config map

set(REGISTERED_TOOLCHAIN_ROOT "c:/Users/harit/.vcpkg/artifacts/fd3d78d7/compilers.arm.armclang/6.20.0/bin")
set(REGISTERED_TOOLCHAIN_VERSION "6.20.0")
set(TOOLCHAIN_VERSION_MIN "6.20.0")
include ("C:/Users/harit/.vcpkg/artifacts/fd3d78d7/tools.open.cmsis.pack.cmsis.toolbox/2.2.0/etc/AC6.6.18.0.cmake")
include ("C:/Users/harit/.vcpkg/artifacts/fd3d78d7/tools.open.cmsis.pack.cmsis.toolbox/2.2.0/etc/CMSIS-Build-Utils.cmake")

# Setup project

project(${TARGET} LANGUAGES AS_ARM C)

cbuild_get_running_toolchain(TOOLCHAIN_ROOT TOOLCHAIN_VERSION C)

# Global Flags

set(CMAKE_AS_ARM_FLAGS "${AS_ARM_CPU} ${AS_ARM_BYTE_ORDER} ${AS_ARM_DEFINES} ${AS_ARM_OPTIONS_FLAGS} ${AS_ARM_FLAGS} ${AS_FLAGS_GLOBAL}")
cbuild_get_system_includes(CC_SYS_INC_PATHS_LIST CC_SYS_INC_PATHS)
set(CMAKE_C_FLAGS "${CC_CPU} ${CC_BYTE_ORDER} ${CC_DEFINES} ${CC_SECURE} ${CC_OPTIONS_FLAGS} ${CC_FLAGS} ${CC_FLAGS_GLOBAL} ${CC_SYS_INC_PATHS}")
set(CMAKE_C_LINK_FLAGS "${LD_CPU} ${_LS}\"${LD_SCRIPT_PP}\" ${LD_SECURE} ${LD_FLAGS_GLOBAL} ${LD_OPTIONS_FLAGS} ${LD_FLAGS}")

# Local Flags

foreach(SRC ${AS_ARM_SRC_FILES})
  set_source_files_properties(${SRC} PROPERTIES LANGUAGE AS_ARM)
endforeach()

# Compilation Database

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(database COMMAND ${CMAKE_COMMAND} -E copy_if_different "${INT_DIR}/compile_commands.json" "${OUT_DIR}")

# Setup Target

add_executable(${TARGET} ${AS_ARM_SRC_FILES} ${CC_SRC_FILES})
set_target_properties(${TARGET} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "mini-project")
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR} LINK_DEPENDS ${LD_SCRIPT})
target_include_directories(${TARGET} PUBLIC ${INC_PATHS})
target_link_libraries(${TARGET} ${LIB_FILES})

# Linker script pre-processing

add_custom_command(TARGET ${TARGET} PRE_LINK COMMAND ${CPP} ARGS ${CPP_ARGS_LD_SCRIPT} BYPRODUCTS ${LD_SCRIPT_PP})
