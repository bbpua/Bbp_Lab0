 /* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"
#define OUTPUT 0
#define INPUT 1
void initLEDs(){
    //TODO: Initialize LEDs
    
    //top led
    TRISDbits.TRISD0 = OUTPUT;  //this 0 is an output
    LATDbits.LATD0 = OUTPUT;
    //middle led
    TRISDbits.TRISD1 = OUTPUT;
    LATDbits.LATD1 = OUTPUT;
    //bottom led
    TRISDbits.TRISD2 = OUTPUT;
    LATDbits.LATD2 = OUTPUT;
}

void turnOnLED(int led){                                //ALL
    //TODO: You may choose to write this function
    // as a matter of convenience
    
    switch(led){
        
        case 0:           //TURNS ON FIRST LED
            
            LATDbits.LATD0 = 1;
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 0;
            break;
            
        case 1:          //TURNS ON 2ND LED
            
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 1;
            LATDbits.LATD2 = 0;
            break;
            
        case 2:          //TURNS ON 3RD LED
            
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 1;
            break;
            
        default:          //ALL LEDS OFF
            
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 0;
            break;
        }
    
}

void turnOffLED(int led){                              //OFF
    
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;

}
////////////////////////part2//////////////////////////
//void turnOnLED1(int led){                               //TOP
//    
//    LATDbits.LATD0 = 1;
//    LATDbits.LATD1 = 0;
//    LATDbits.LATD2 = 0;
//
//
//}
//
//void turnOnLED2(int led){                              //MID
//    
//    LATDbits.LATD0 = 0;
//    LATDbits.LATD1 = 1;
//    LATDbits.LATD2 = 0;
//
//
//}
//
//
//void turnOnLED3(int led){                              //BOTTOM
//    
//    LATDbits.LATD0 = 0;
//    LATDbits.LATD1 = 0;
//    LATDbits.LATD2 = 1;
//
//
//}
////////////////////////////////part2////////////////////