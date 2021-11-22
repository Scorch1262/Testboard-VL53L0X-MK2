#include <xc.h>
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/i2c_master.h"
#include "mcc_generated_files/examples/i2c_master_example.h"
#include "vl53l0x.h"

#define SYSRANGE_START                              0x00
#define SYSTEM_THRESH_HIGH                          0x0C
#define SYSTEM_THRESH_LOW                           0x0E
#define SYSTEM_SEQUENCE_CONFIG                      0x01
#define SYSTEM_RANGE_CONFIG                         0x09
#define SYSTEM_INTERMEASUREMENT_PERIOD              0x04
#define SYSTEM_INTERRUPT_CONFIG_GPIO                0x0A
#define GPIO_HV_MUX_ACTIVE_HIGH                     0x84
#define SYSTEM_INTERRUPT_CLEAR                      0x0B
#define RESULT_INTERRUPT_STATUS                     0x13
#define RESULT_RANGE_STATUS                         0x14
#define RESULT_CORE_AMBIENT_WINDOW_EVENTS_RTN       0xBC
#define RESULT_CORE_RANGING_TOTAL_EVENTS_RTN        0xC0
#define RESULT_CORE_AMBIENT_WINDOW_EVENTS_REF       0xD0
#define RESULT_CORE_RANGING_TOTAL_EVENTS_REF        0xD4
#define RESULT_PEAK_SIGNAL_RATE_REF                 0xB6
#define ALGO_PART_TO_PART_RANGE_OFFSET_MM           0x28
#define I2C_SLAVE_DEVICE_ADDRESS                    0x8A
#define MSRC_CONFIG_CONTROL                         0x60
#define PRE_RANGE_CONFIG_MIN_SNR                    0x27
#define PRE_RANGE_CONFIG_VALID_PHASE_LOW            0x56
#define PRE_RANGE_CONFIG_VALID_PHASE_HIGH           0x57
#define PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT          0x64
#define FINAL_RANGE_CONFIG_MIN_SNR                  0x67
#define FINAL_RANGE_CONFIG_VALID_PHASE_LOW          0x47
#define FINAL_RANGE_CONFIG_VALID_PHASE_HIGH         0x48
#define FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT 0x44
#define PRE_RANGE_CONFIG_SIGMA_THRESH_HI            0x61
#define PRE_RANGE_CONFIG_SIGMA_THRESH_LO            0x62
#define PRE_RANGE_CONFIG_VCSEL_PERIOD               0x50
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI          0x51
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO          0x52
#define SYSTEM_HISTOGRAM_BIN                        0x81
#define HISTOGRAM_CONFIG_INITIAL_PHASE_SELECT       0x33
#define HISTOGRAM_CONFIG_READOUT_CTRL               0x55
#define FINAL_RANGE_CONFIG_VCSEL_PERIOD             0x70
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI        0x71
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO        0x72
#define CROSSTALK_COMPENSATION_PEAK_RATE_MCPS       0x20
#define MSRC_CONFIG_TIMEOUT_MACROP                  0x46
#define SOFT_RESET_GO2_SOFT_RESET_N                 0xBF
#define IDENTIFICATION_MODEL_ID                     0xC0
#define IDENTIFICATION_REVISION_ID                  0xC2
#define OSC_CALIBRATE_VAL                           0xF8
#define GLOBAL_CONFIG_VCSEL_WIDTH                   0x32
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_0            0xB0
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_1            0xB1
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_2            0xB2
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_3            0xB3
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_4            0xB4
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_5            0xB5
#define GLOBAL_CONFIG_REF_EN_START_SELECT           0xB6
#define DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD         0x4E
#define DYNAMIC_SPAD_REF_EN_START_OFFSET            0x4F
#define POWER_MANAGEMENT_GO1_POWER_FORCE            0x80
#define VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV           0x89
#define ALGO_PHASECAL_LIM                           0x30
#define ALGO_PHASECAL_CONFIG_TIMEOUT                0x30

uint8_t  writeBuffer[16] = {0x00, 0x00, 0x00};                                          // definiert "writeBuffer"
uint8_t  readBuffer[16] = {0x00, 0x00};                                                 // definiert "readBuffer"

void VL53L0X_Init(void){                                                                // "VL53L0X_Init"
    uint16_t    data16;                                                                 // definiert "data16"
    uint8_t     data8;                                                                  // definiert "data8"    
    
    #define VL53L0X_ADDR    0x29
    
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV);     // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV, 0x01);      // 
    I2C_Write1ByteRegister(VL53L0X_ADDR,0x88,0x00);                                     // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_CORE_RANGING_TOTAL_EVENTS_RTN);  // 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, OSC_CALIBRATE_VAL);                    // 
        writeBuffer[0] = SYSTEM_INTERMEASUREMENT_PERIOD;                                // 
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);                                  // 
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);                                    // 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, CROSSTALK_COMPENSATION_PEAK_RATE_MCPS);// 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, ALGO_PART_TO_PART_RANGE_OFFSET_MM);    // 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT);// 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT);   // 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT);   // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);                // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);                // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);         // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_TIMEOUT_MACROP);            // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);         // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);         // 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);   // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);                // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);         // 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);   // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VCSEL_PERIOD);       // 
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI); //
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);       // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);                                   // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);                                   // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x91);                                  // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);                                   // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);                                   // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);       // 
        writeBuffer[0] = 0x44;                                                          // 
        writeBuffer[1] = 0x00;                                                          // 
        writeBuffer[2] = 0x20;                                                          // 
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 3);                                  // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL);                   // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL, 0x00);                    // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL);                   // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL, 0x00);                    // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL);                   // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL, 0x02);                    // 
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL);                   // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL, 0x12);                    // 
        writeBuffer[0] = 0x44;                                                          // 
        writeBuffer[1] = 0x00;                                                          // 
        writeBuffer[2] = 0x20;                                                          // 
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 3);                                  // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xFF);                 // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, I2C_SLAVE_DEVICE_ADDRESS, VL53L0X_ADDR);                           // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);       // 
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x06);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x05);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x07);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_HISTOGRAM_BIN, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x02);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x90);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x7B);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x90);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x77);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
        writeBuffer[0] = 0x90;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x78);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
        writeBuffer[0] = 0x90;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x79);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
        writeBuffer[0] = 0x90;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x7A);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
        writeBuffer[0] = 0x90;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_HISTOGRAM_BIN, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x06);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_CORE_RANGING_TOTAL_EVENTS_RTN);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, IDENTIFICATION_REVISION_ID);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x06);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x05);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x07);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_HISTOGRAM_BIN, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x6B);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
        writeBuffer[0] = 0x90;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x24);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
        writeBuffer[0] = 0x90;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x94, 0x25);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
        writeBuffer[0] = 0x90;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_HISTOGRAM_BIN, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x06);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x83, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF, 0xB4);
        writeBuffer[0] = GLOBAL_CONFIG_SPAD_ENABLES_REF_0;
        writeBuffer[1] = 0x00;
        writeBuffer[2] = 0xF0;
        writeBuffer[3] = 0xE7;
        writeBuffer[4] = 0x3F;
        writeBuffer[5] = 0x00;
        writeBuffer[6] = 0x00;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 7);
        writeBuffer[0] = GLOBAL_CONFIG_SPAD_ENABLES_REF_0;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 6);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_RANGE_CONFIG, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x10, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x11, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x24, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x25, 0xFF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x75, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x30, 0x20);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x30, 0x09);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x54, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x31, 0x04);
    I2C_Write1ByteRegister(VL53L0X_ADDR, GLOBAL_CONFIG_VCSEL_WIDTH, 0x03);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x40, 0x83);
    I2C_Write1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_TIMEOUT_MACROP, 0x25);
    I2C_Write1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_CONTROL, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_MIN_SNR, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD, 0x06);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0x96);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VALID_PHASE_LOW, 0x08);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VALID_PHASE_HIGH, 0x30);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_SIGMA_THRESH_HI, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_SIGMA_THRESH_LO, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x65, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x66, 0xA0);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x22, 0x32);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VALID_PHASE_LOW, 0x14);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x49, 0xFF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x4A, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x7A, 0x0A);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x7B, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x78, 0x21);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x23, 0x34);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x42, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 0xFF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x45, 0x26);
    I2C_Write1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_TIMEOUT_MACROP, 0x05);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x40, 0x40);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_THRESH_LOW, 0x06);
    I2C_Write1ByteRegister(VL53L0X_ADDR, CROSSTALK_COMPENSATION_PEAK_RATE_MCPS, 0x1A);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x43, 0x40);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x34, 0x03);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x35, 0x44);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x31, 0x04);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x4B, 0x09);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x4C, 0x05);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x4D, 0x04);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x45, 0x20);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VALID_PHASE_LOW, 0x08);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x28);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_MIN_SNR, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VCSEL_PERIOD, 0x04);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0xFE);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x76, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x77, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x0D, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xF8);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x8E, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, GPIO_HV_MUX_ACTIVE_HIGH);
    I2C_Write1ByteRegister(VL53L0X_ADDR, GPIO_HV_MUX_ACTIVE_HIGH, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, GPIO_HV_MUX_ACTIVE_HIGH);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, OSC_CALIBRATE_VAL);
        writeBuffer[0] = SYSTEM_INTERMEASUREMENT_PERIOD;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 4);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, CROSSTALK_COMPENSATION_PEAK_RATE_MCPS);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, ALGO_PART_TO_PART_RANGE_OFFSET_MM);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_TIMEOUT_MACROP);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_RANGE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xE8);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, MSRC_CONFIG_TIMEOUT_MACROP);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VCSEL_PERIOD);
        writeBuffer[0] = 0x71;
        writeBuffer[1] = 0x02;
        writeBuffer[2] = 0x94;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 3);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VCSEL_PERIOD);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_VCSEL_PERIOD);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF, 0xB4);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x41);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0x02);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xE8);
        writeBuffer[0] = GLOBAL_CONFIG_SPAD_ENABLES_REF_0;
        writeBuffer[1] = 0x07;
        writeBuffer[2] = 0x00;
        writeBuffer[3] = 0x00;
        writeBuffer[4] = 0x00;
        writeBuffer[5] = 0x00;
        writeBuffer[6] = 0x00;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 7);
        writeBuffer[0] = GLOBAL_CONFIG_SPAD_ENABLES_REF_0;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 6);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xC0);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x91, 0x3C);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
        writeBuffer[0] = RESULT_RANGE_STATUS;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 12);                 
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xE8);
        writeBuffer[0] = GLOBAL_CONFIG_SPAD_ENABLES_REF_0;
        writeBuffer[1] = 0x0F;
        writeBuffer[2] = 0x00;
        writeBuffer[3] = 0x00;
        writeBuffer[4] = 0x00;
        writeBuffer[5] = 0x00;
        writeBuffer[6] = 0x00;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 7);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xC0);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x91, 0x3C);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
        writeBuffer[0] = RESULT_RANGE_STATUS;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 12);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xE8);
        writeBuffer[0] = GLOBAL_CONFIG_SPAD_ENABLES_REF_0;
        writeBuffer[1] = 0x1F;
        writeBuffer[2] = 0x00;
        writeBuffer[3] = 0x00;
        writeBuffer[4] = 0x00;
        writeBuffer[5] = 0x00;
        writeBuffer[6] = 0x00;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 7);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xC0);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x91, 0x3C);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
        writeBuffer[0] = RESULT_RANGE_STATUS;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 1);
    I2C_ReadNBytes(VL53L0X_ADDR, &readBuffer[0], 12);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    data16 = I2C_Read2ByteRegister(VL53L0X_ADDR, RESULT_PEAK_SIGNAL_RATE_REF);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xE8);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x41);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0xCB);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0x02);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_INTERRUPT_CLEAR, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, RESULT_INTERRUPT_STATUS);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    data8 = I2C_Read1ByteRegister(VL53L0X_ADDR, 0xEE);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0x00, 0x01);
    I2C_Write1ByteRegister(VL53L0X_ADDR, 0xFF, 0x00);
    I2C_Write1ByteRegister(VL53L0X_ADDR, SYSTEM_SEQUENCE_CONFIG, 0xE8);
        writeBuffer[0] = 0x44;
        writeBuffer[1] = 0x00;
        writeBuffer[2] = 0x20;
    I2C_WriteNBytes(VL53L0X_ADDR, &writeBuffer[0], 3);

    __delay_ms(10);                                                                     // warte 10ms
}                                                                                       //


void VL53L0X_SetAdd(uint8_t new){
    uint16_t    data16;                                                                 // definiert "data16"
    uint8_t     data8;                                                                  // definiert "data8"    
    
    #define VL53L0X_ADDR    0x29
  
    I2C_Write1ByteRegister(VL53L0X_ADDR, I2C_SLAVE_DEVICE_ADDRESS, new);               // 
}


float VL53L0X_Millimeter_GetValue(uint8_t addr){                                                // "VL53L0X_Millimeter_GetValue"
    float       DistDistanzAnz;                                                         // definiert "DistDistanzAnz"
    uint16_t    data16;                                                                 // definiert "data16"
    uint8_t     data8;                                                                  // definiert "data8"

    
    I2C_Write1ByteRegister(addr, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);       // 
    I2C_Write1ByteRegister(addr, 0xFF, 0x01);                                   // 
    I2C_Write1ByteRegister(addr, 0x00, 0x00);                                   // 
    I2C_Write1ByteRegister(addr, 0x91, 0x3C);                                   // 
    I2C_Write1ByteRegister(addr, 0x00, 0x01);                                   // 
    I2C_Write1ByteRegister(addr, 0xFF, 0x00);                                   // 
    I2C_Write1ByteRegister(addr, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);       // 
    I2C_Write1ByteRegister(addr, 0x00, 0x01);                                   // 
    data8 = I2C_Read1ByteRegister(addr, 0x00);                                  // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 
        writeBuffer[0] = 0x1E; //RESULT_RANGE_STATUS                                    // 
    I2C_WriteNBytes(addr, &writeBuffer[0], 1);                                  // 
    I2C_ReadNBytes(addr, &readBuffer[0], 12);                                   // 
    I2C_Write1ByteRegister(addr, 0xFF, 0x01);                                   // 
    data16 = I2C_Read2ByteRegister(addr, RESULT_PEAK_SIGNAL_RATE_REF);          // 
    I2C_Write1ByteRegister(addr, 0xFF, 0x00);                                   // 
    I2C_Write1ByteRegister(addr, SYSTEM_INTERRUPT_CLEAR, 0x01);                 // 
    I2C_Write1ByteRegister(addr, SYSTEM_INTERRUPT_CLEAR, 0x00);                 // 
    data8 = I2C_Read1ByteRegister(addr, RESULT_INTERRUPT_STATUS);               // 

    data16 = (readBuffer[0] << 8) + readBuffer[1];                                      // 
    DistDistanzAnz = data16;                                                            // kopiert "data16" in "DistDistanzAnz"
    
    return DistDistanzAnz;                                                              // gibt "DistDistanzAnz" zur?ck
}                                                                                       //
