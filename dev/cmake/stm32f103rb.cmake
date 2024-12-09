# STM32F103RB specific commands
set(CONAN_OPTION_PLATFORM stm32f103rb)

# Compiler and linker options
set(CPU_OPTIONS -mthumb -mcpu=cortex-m3)
set(LINKER_SCRIPT "dev/linkers/${CONAN_OPTION_PLATFORM}.ld")

# Add startup files
set(STARTUP_FILES
    src/startup/stm32f10x/handlers.cpp
    src/startup/stm32f10x/startup.cpp
)