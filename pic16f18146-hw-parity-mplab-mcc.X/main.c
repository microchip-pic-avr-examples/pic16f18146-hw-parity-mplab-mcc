 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

#include <stdint.h>
#include <stdbool.h>

//How much data is in the array
#define DATA_ARRAY_SIZE 10

//How much data to scan
#define DATA_SCAN_LENGTH 10

//Data to scan
static uint8_t data[DATA_ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

//Should the test be run?
static volatile bool runTest = true;

//Trigger a new test run
void onButtonPress(void)
{
    runTest = true;
}

//Software based 
bool isOdd_SW(void)
{
    bool isOdd = false;
    uint8_t temp;
    
    //Byte Scan
    for (uint8_t byIndex = 0; byIndex < DATA_SCAN_LENGTH; byIndex++)
    {
        //Bit Scan
        temp = data[byIndex];
        for (uint8_t biIndex = 0; biIndex != 8; biIndex++)
        {
            if (temp & 0b1)
            {
                //Count
                isOdd = !isOdd;
            }
            
            //Shift bits
            temp >>= 1;
        }
    }
    return (isOdd);
}

bool isOdd_HW(void)
{
    bool initialState = CLC3_OutputStatusGet();
    SPI1_BufferWrite(&data[0], DATA_SCAN_LENGTH);
    return (!(CLC3_OutputStatusGet() == initialState));
}

int main(void)
{
    SYSTEM_Initialize();

    CLC2_CLCI_SetInterruptHandler(&onButtonPress);
    
    //Configure SPI
    SPI1_Open(0);
    
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    bool odd = false;
    
    while(1)
    {
        if (runTest)
        {
            printf("Calculating Parity on %d bytes...\r\n\r\n", DATA_SCAN_LENGTH);
            
            printf("Software Parity\r\n");
            
            //Clear Timer 1
            Timer1_Write(0x0000);
            
            //First, SW Driven
            
            //Start
            Timer1_Start();
            odd = isOdd_SW();
            Timer1_Stop();
            
            printf("Computation Time: %d\r\nIs Odd: ", Timer1_Read());
            
            if (odd)
            {
                printf("Yes\r\n");
            }
            else
            {
                printf("No\r\n");
            }
            
            //Now, HW Driven
            
            printf("\r\nHardware Accelerated Parity\r\n");
            
            //Clear Timer 1
            Timer1_Write(0x0000);

            //Start
            Timer1_Start();
            odd = isOdd_HW();
            Timer1_Stop();
            
            printf("Computation Time: %d\r\nIs Odd: ", Timer1_Read());
            
            if (odd)
            {
                printf("Yes\r\n");
            }
            else
            {
                printf("No\r\n");
            }
            
            printf("\r\n");
            runTest = false;
        }
    }    
}