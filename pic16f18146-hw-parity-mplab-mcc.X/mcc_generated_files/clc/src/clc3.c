/**
 * CLC3 Generated Driver File.
 * 
 * @file clc3.c
 * 
 * @ingroup  clc3
 * 
 * @brief This file contains the API implementations for the CLC3 driver.
 *
 * @version CLC3 Driver Version 1.0.1
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


#include <xc.h>
#include "../clc3.h"


void CLC3_Initialize(void)
{
    
    // SLCT 0x2; 
    CLCSELECT = 0x2;
    // LCG1POL not_inverted; LCG2POL inverted; LCG3POL not_inverted; LCG4POL inverted; LCPOL not_inverted; 
    CLCnPOL = 0xA;
    // LCD1S SPI1 SDO OUT; 
    CLCnSEL0 = 0x29;
    // LCD2S CLC3_OUT; 
    CLCnSEL1 = 0x25;
    // LCD3S CLC3_OUT; 
    CLCnSEL2 = 0x25;
    // LCD4S SPI1 SCK OUT; 
    CLCnSEL3 = 0x2A;
    // LCG1D1N disabled; LCG1D1T disabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T enabled; 
    CLCnGLS0 = 0x80;
    // LCG2D1N disabled; LCG2D1T enabled; LCG2D2N enabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = 0x6;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = 0x0;
    // LCG4D1N enabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T enabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = 0x9;
    // LCOUT 0x00; 
    CLCDATA = 0x0;
    // LCMODE 2-input D flip-flop with R; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = 0x85;

}


bool CLC3_OutputStatusGet(void)
{
    return(CLCDATAbits.CLC3OUT);
}
/**
 End of File
*/
