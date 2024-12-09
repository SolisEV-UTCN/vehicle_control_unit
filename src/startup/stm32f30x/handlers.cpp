/**
 * Handlers setup code for Cortex-M.
 */
// clang-format off
extern "C" {
typedef void (*ptr_func_t)(void);

// Undefined Cortex handler is pointing to this function, this stop MCU.
// This function name must by not mangled, so must be C,
// because alias("..") is working only with C code
void __stop() { while (true); }

// Undefined IRQ handler is pointing to this function, this ignores interrupt.
// This function name must by not mangled, so must be C,
// because alias("..") is working only with C code
void __skip() { return; }

// Defined in linker script
extern unsigned _estack;

// Initial stack pointer is first address of program
__attribute__((section(".stack"), used)) unsigned *__stack_init = &_estack;

// Handlers for Cortex-M core
// These handler are with attribute 'weak' and can be overwritten
// by non-week function, default is __stop() function
__attribute__((weak, alias("__stop"))) void RESET_handler();
__attribute__((weak, alias("__stop"))) void NMI_handler();
__attribute__((weak, alias("__stop"))) void HARDFAULT_handler();
__attribute__((weak, alias("__stop"))) void MEMMANAGE_handler();
__attribute__((weak, alias("__stop"))) void BUSFAULT_handler();
__attribute__((weak, alias("__stop"))) void USAGEFAULT_handler();
__attribute__((weak, alias("__stop"))) void SVCALL_handler();
__attribute__((weak, alias("__stop"))) void PENDSV_handler();
__attribute__((weak, alias("__stop"))) void SYSTICK_handler();

// Dummy handler (for unused vectors)
__attribute__((weak, alias("__stop"))) void DUMMY_handler();

// STM32F10xxx IRQ handlers
// These handler are with attribute 'weak' and can be overwritten
// by non-week function, default is __skip() function
__attribute__((weak, alias("__skip"))) void WWDG_handler();
__attribute__((weak, alias("__skip"))) void PVD_handler();
__attribute__((weak, alias("__skip"))) void TAMPER_STAMP_handler();
__attribute__((weak, alias("__skip"))) void RTC_WKUP_handler();
__attribute__((weak, alias("__skip"))) void FLASH_handler();
__attribute__((weak, alias("__skip"))) void RCC_handler();
__attribute__((weak, alias("__skip"))) void EXTI0_handler();
__attribute__((weak, alias("__skip"))) void EXTI1_handler();
__attribute__((weak, alias("__skip"))) void EXTI2_TS_handler();
__attribute__((weak, alias("__skip"))) void EXTI3_handler();
__attribute__((weak, alias("__skip"))) void EXTI4_handler();
__attribute__((weak, alias("__skip"))) void DMA1_Channel1_handler();
__attribute__((weak, alias("__skip"))) void DMA1_Channel2_handler();
__attribute__((weak, alias("__skip"))) void DMA1_Channel3_handler();
__attribute__((weak, alias("__skip"))) void DMA1_Channel4_handler();
__attribute__((weak, alias("__skip"))) void DMA1_Channel5_handler();
__attribute__((weak, alias("__skip"))) void DMA1_Channel6_handler();
__attribute__((weak, alias("__skip"))) void DMA1_Channel7_handler();
__attribute__((weak, alias("__skip"))) void ADC1_2_handler();
__attribute__((weak, alias("__skip"))) void USB_HP_CAN1_TX_handler();
__attribute__((weak, alias("__skip"))) void USB_LP_CAN1_RX0_handler();
__attribute__((weak, alias("__skip"))) void CAN1_RX1_handler();
__attribute__((weak, alias("__skip"))) void CAN1_SCE_handler();
__attribute__((weak, alias("__skip"))) void EXTI9_5_handler();
__attribute__((weak, alias("__skip"))) void TIM1_BRK_TIM15_handler();
__attribute__((weak, alias("__skip"))) void TIM1_UP_TIM16_handler();
__attribute__((weak, alias("__skip"))) void TIM1_TRG_COM_TIM17_handler();
__attribute__((weak, alias("__skip"))) void TIM1_CC_handler();
__attribute__((weak, alias("__skip"))) void TIM2_handler();
__attribute__((weak, alias("__skip"))) void TIM3_handler();
__attribute__((weak, alias("__skip"))) void TIM4_handler();
__attribute__((weak, alias("__skip"))) void I2C1_EV_handler();
__attribute__((weak, alias("__skip"))) void I2C1_ER_handler();
__attribute__((weak, alias("__skip"))) void I2C2_EV_handler();
__attribute__((weak, alias("__skip"))) void I2C2_ER_handler();
__attribute__((weak, alias("__skip"))) void SPI1_handler();
__attribute__((weak, alias("__skip"))) void SPI2_handler();
__attribute__((weak, alias("__skip"))) void USART1_handler();
__attribute__((weak, alias("__skip"))) void USART2_handler();
__attribute__((weak, alias("__skip"))) void USART3_handler();
__attribute__((weak, alias("__skip"))) void EXTI15_10_handler();
__attribute__((weak, alias("__skip"))) void RTC_Alarm_handler();
__attribute__((weak, alias("__skip"))) void USBWakeUp_handler();
__attribute__((weak, alias("__skip"))) void TIM8_BRK_handler();
__attribute__((weak, alias("__skip"))) void TIM8_UP_handler();
__attribute__((weak, alias("__skip"))) void TIM8_TRG_COM_handler();
__attribute__((weak, alias("__skip"))) void TIM8_CC_handler();
__attribute__((weak, alias("__skip"))) void ADC3_handler();
__attribute__((weak, alias("__skip"))) void FMC_handler();
__attribute__((weak, alias("__skip"))) void SPI3_handler();
__attribute__((weak, alias("__skip"))) void UART4_handler();
__attribute__((weak, alias("__skip"))) void UART5_handler();
__attribute__((weak, alias("__skip"))) void TIM6_DAC_handler();
__attribute__((weak, alias("__skip"))) void TIM7_handler();
__attribute__((weak, alias("__skip"))) void DMA2_Channel1_handler();
__attribute__((weak, alias("__skip"))) void DMA2_Channel2_handler();
__attribute__((weak, alias("__skip"))) void DMA2_Channel3_handler();
__attribute__((weak, alias("__skip"))) void DMA2_Channel4_handler();
__attribute__((weak, alias("__skip"))) void DMA2_Channel5_handler();
__attribute__((weak, alias("__skip"))) void ADC4_handler();
__attribute__((weak, alias("__skip"))) void COMP1_2_3_handler();
__attribute__((weak, alias("__skip"))) void COMP4_5_6_handler();
__attribute__((weak, alias("__skip"))) void COMP7_handler();
__attribute__((weak, alias("__skip"))) void USB_HP_handler();
__attribute__((weak, alias("__skip"))) void USB_LP_handler();
__attribute__((weak, alias("__skip"))) void USB_WakeUp_RMP_handler();
__attribute__((weak, alias("__skip"))) void FPU_handler();

// Vector table for handlers
// This array will be placed in ".isr_vector" section defined in linker script.
__attribute__((aligned(128), section(".isr_vector"), used))
ptr_func_t __isr_vectors[] = {
  reinterpret_cast<ptr_func_t>(&_estack),  // 0x0800_0000 |
  RESET_handler,                           // 0x0800_0004 | Cortex-M Interrupts
  NMI_handler,                             // 0x0800_0008 |
  HARDFAULT_handler,                       // 0x0800_000C |
  MEMMANAGE_handler,                       // 0x0800_0010 |
  BUSFAULT_handler,                        // 0x0800_0014 |
  USAGEFAULT_handler,                      // 0x0800_0018 |
  DUMMY_handler,                           // 0x0800_001C |
  DUMMY_handler,                           // 0x0800_0020 |
  DUMMY_handler,                           // 0x0800_0024 |
  DUMMY_handler,                           // 0x0800_0028 |
  SVCALL_handler,                          // 0x0800_002C |
  DUMMY_handler,                           // 0x0800_0030 |
  DUMMY_handler,                           // 0x0800_0034 |
  PENDSV_handler,                          // 0x0800_0038 |
  SYSTICK_handler,                         // 0x0800_003C /
  WWDG_handler,                            // 0x0800_0040 |
  PVD_handler,                             // 0x0800_0044 | STM32F10xxx Interrupts
  TAMPER_STAMP_handler,                    // 0x0800_0048 |
  RTC_WKUP_handler,                        // 0x0800_004C |
  FLASH_handler,                           // 0x0800_0050 |
  RCC_handler,                             // 0x0800_0054 |
  EXTI0_handler,                           // 0x0800_0058 |
  EXTI1_handler,                           // 0x0800_005C |
  EXTI2_TS_handler,                        // 0x0800_0060 |
  EXTI3_handler,                           // 0x0800_0064 |
  EXTI4_handler,                           // 0x0800_0068 |
  DMA1_Channel1_handler,                   // 0x0800_006C |
  DMA1_Channel2_handler,                   // 0x0800_0070 |
  DMA1_Channel3_handler,                   // 0x0800_0074 |
  DMA1_Channel4_handler,                   // 0x0800_0078 |
  DMA1_Channel5_handler,                   // 0x0800_007C |
  DMA1_Channel6_handler,                   // 0x0800_0080 |
  DMA1_Channel7_handler,                   // 0x0800_0084 |
  ADC1_2_handler,                          // 0x0800_0088 |
  USB_HP_CAN1_TX_handler,                  // 0x0800_008C |
  USB_LP_CAN1_RX0_handler,                 // 0x0800_0090 |
  CAN1_RX1_handler,                        // 0x0800_0094 |
  CAN1_SCE_handler,                        // 0x0800_0098 |
  EXTI9_5_handler,                         // 0x0800_009C |
  TIM1_BRK_TIM15_handler,                  // 0x0800_00A0 |
  TIM1_UP_TIM16_handler,                   // 0x0800_00A4 |
  TIM1_TRG_COM_TIM17_handler,              // 0x0800_00A8 |
  TIM1_CC_handler,                         // 0x0800_00AC |
  TIM2_handler,                            // 0x0800_00B0 |
  TIM3_handler,                            // 0x0800_00B4 |
  TIM4_handler,                            // 0x0800_00B8 |
  I2C1_EV_handler,                         // 0x0800_00BC |
  I2C1_ER_handler,                         // 0x0800_00C0 |
  I2C2_EV_handler,                         // 0x0800_00C4 |
  I2C2_ER_handler,                         // 0x0800_00C8 |
  SPI1_handler,                            // 0x0800_00CC |
  SPI2_handler,                            // 0x0800_00D0 |
  USART1_handler,                          // 0x0800_00D4 |
  USART2_handler,                          // 0x0800_00D8 |
  USART3_handler,                          // 0x0800_00DC |
  EXTI15_10_handler,                       // 0x0800_00E0 |
  RTC_Alarm_handler,                       // 0x0800_00E4 |
  USBWakeUp_handler,                       // 0x0800_00E8 |
  TIM8_BRK_handler,                        // 0x0800_00EC |
  TIM8_UP_handler,                         // 0x0800_00F0 |
  TIM8_TRG_COM_handler,                    // 0x0800_00F4 |
  TIM8_CC_handler,                         // 0x0800_00F8 |
  ADC3_handler,                            // 0x0800_00FC |
  DUMMY_handler,                           // 0x0800_0100 |
  DUMMY_handler,                           // 0x0800_0104 |
  DUMMY_handler,                           // 0x0800_0108 |
  SPI3_handler,                            // 0x0800_010C |
  UART4_handler,                           // 0x0800_0110 |
  UART5_handler,                           // 0x0800_0114 |
  TIM6_DAC_handler,                        // 0x0800_0118 |
  TIM7_handler,                            // 0x0800_011C |
  DMA2_Channel1_handler,                   // 0x0800_0120 |
  DMA2_Channel2_handler,                   // 0x0800_0124 |
  DMA2_Channel3_handler,                   // 0x0800_0128 |
  DMA2_Channel4_handler,                   // 0x0800_012C |
  DMA2_Channel5_handler,                   // 0x0800_0130 |
  ADC4_handler,                            // 0x0800_0134 |
  DUMMY_handler,                           // 0x0800_0138 |
  DUMMY_handler,                           // 0x0800_013C |
  COMP1_2_3_handler,                       // 0x0800_0140 |
  COMP4_5_6_handler,                       // 0x0800_0144 |
  COMP7_handler,                           // 0x0800_0148 |
  DUMMY_handler,                           // 0x0800_014C |
  DUMMY_handler,                           // 0x0800_0150 |
  DUMMY_handler,                           // 0x0800_0154 |
  DUMMY_handler,                           // 0x0800_0158 |
  DUMMY_handler,                           // 0x0800_015C |
  DUMMY_handler,                           // 0x0800_0160 |
  DUMMY_handler,                           // 0x0800_0164 |
  USB_HP_handler,                          // 0x0800_0168 |
  USB_LP_handler,                          // 0x0800_016C |
  USB_WakeUp_RMP_handler,                  // 0x0800_0170 |
  DUMMY_handler,                           // 0x0800_0174 |
  DUMMY_handler,                           // 0x0800_0178 |
  DUMMY_handler,                           // 0x0800_017C |
  DUMMY_handler,                           // 0x0800_0180 |
  FPU_handler,                             // 0x0800_0184 |
  DUMMY_handler,                           // 0x0800_0188 |
  DUMMY_handler,                           // 0x0800_018C |
  DUMMY_handler                            // 0x0800_0190 |
};
}
// clang-format on
