# STM32F303CB specific commands
set(CONAN_OPTION_PLATFORM stm32f303cb)

# Compiler and linker options
set(CPU_OPTIONS -mthumb -mcpu=cortex-m4)
set(LINKER_SCRIPT "dev/linkers/${CONAN_OPTION_PLATFORM}.ld")

# Add startup files
set(STARTUP_FILES
    src/startup/stm32f30x/handlers.cpp
    src/startup/stm32f30x/startup.cpp
)