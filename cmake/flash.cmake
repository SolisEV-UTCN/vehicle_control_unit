# CMake script for generating binary format, hex format and flash files
if(NOT CMAKE_OBJCOPY)
    message(FATAL_ERROR "objcopy not found, please install it or specify its path.")
endif()

if(NOT CMAKE_NM)
    message(FATAL_ERROR "nm not found, please install it or specify its path.")
endif()

add_custom_command(OUTPUT ${PROJECT_NAME}.srec
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Osrec ${PROJECT_NAME} ${PROJECT_NAME}.srec
)
add_custom_command(OUTPUT ${PROJECT_NAME}.hex
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
)
add_custom_command(OUTPUT ${PROJECT_NAME}.bin
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)
add_custom_command(OUTPUT ${PROJECT_NAME}.lst
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJDUMP} -S ${PROJECT_NAME} > ${PROJECT_NAME}.lst
)
add_custom_command(OUTPUT ${PROJECT_NAME}.sym
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_NM} -C -l -n -S ${PROJECT_NAME} > ${PROJECT_NAME}.sym
)

add_custom_target(srec
    ALL DEPENDS ${PROJECT_NAME}.srec
)
add_custom_target(hex
    ALL DEPENDS ${PROJECT_NAME}.hex
)
add_custom_target(bin
    ALL DEPENDS ${PROJECT_NAME}.bin
)
add_custom_target(lst
    ALL DEPENDS ${PROJECT_NAME}.lst
)
add_custom_target(sym
    ALL DEPENDS ${PROJECT_NAME}.sym
)
add_custom_target(flash
    pystlink flash:erase:verify:${PROJECT_NAME}.srec
    ALL DEPENDS ${PROJECT_NAME}.srec
)
