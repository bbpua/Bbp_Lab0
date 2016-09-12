/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include <proc/p32mx470f512l.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

#define PRESSED 0
#define RELEASED 1

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    start,
            
            
    WP,  // wait press    
    DP, //debounce press
    WR,  //wait release
    DR,   //debounce release
            
    DP2,
    WR2,
    DR2,
    
    starthalfsecond,
            
    leddown,
    ledup,
            

} stateType;

stateType nextstate = start;   //initial state will be led1

//TODO: Use volatile variables that change within interrupts

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initSwitch1();
    initTimer1();
    initLEDs();
    int led;
    
 //////////////////////////////////PART3////////////////////////////////////
    while(1){
        
        switch(nextstate){
            
           
            
            case start:
                    
                
                led = 0;
                turnOnLED(0);
                nextstate = WP;
                break;
          //////////////////////FIRST PRESS///////////////////  
                case WP:
                    
                    if (PORTDbits.RD6 == PRESSED){
                    TMR1CLR = 0xFFFF;; // Clear the timer interrupt flag
                    nextstate = DP;
                    //T1CONbits.TON = 1;//enable timer
                    IFS0bits.T1IF = 0;//flag down
                    
                    }
                    else nextstate = WP;
                    
                break;
                
            case DP: 
                nextstate = WR;
                break;
         
                
            case WR:
                
                if(PORTDbits.RD6 == RELEASED)
                { 
                        nextstate = DR;
                         
                }
                else{
                    nextstate = WR;
                }
                break;
                
            case DR:
                nextstate = starthalfsecond;
                
                break;
                
            case starthalfsecond:
                
                halfsecondTimer();
                 if(PORTDbits.RD6 == PRESSED && halfsecondTimer()== 666763256)//check if the flag is on
                    {
                        nextstate = DP2;//move to the previous state if the flag is on when hold more than 2 seconds
                        T1CONbits.TON = 0;//clear the timer when not in use
                 }
                 else{
                nextstate = leddown;
                T1CONbits.TON = 0;//clear the timer when not in use
                 }
                break;
                
            case DP2:
                if(PORTDbits.RD6 == 0)
                    {
                        nextstate = WR2;//move to the previous state if the flag is on when hold more than 2 seconds
                        T1CONbits.TON = 0;//clear the timer when not in use
                 }
                 else{
                nextstate = leddown;
                T1CONbits.TON = 0;//clear the timer when not in use
                 }
                
                nextstate = WR2;
                break;
                
            case WR2:
                if(PORTDbits.RD6 == RELEASED)//check if the flag is on
                    {
                        nextstate = ledup;//move to the previous state if the flag is on when hold more than 2 seconds
                        T1CONbits.TON = 0;//clear the timer when not in use
                 }
                 else{
                nextstate = leddown;
                T1CONbits.TON = 0;//clear the timer when not in use
                 }
                
                break;
                
                
                
                
           
                
             
         //////////////////////FIRST PRESS///////////////////
                
         
                
        //////////////////////SECOND PRESS///////////////////      
//            case DP2:
//                
//                    nextstate = WR2;
//                    turnOffLED(1);
//                break;
//                
//            case WR2:
//                
//                if (PORTDbits.RD6 == RELEASED){
//                    nextstate = DR2;
//                }
//                break;
//                
//            case DR2:
//                
//                    nextstate = led1up;
//                
//                break;
         //////////////////////SECOND PRESS///////////////////
                
                
                
                
       //////////////////////DOWNWARD///////////////  
                
            case leddown:
                
                
                
                if(led == 0){
                    led = 1;
                }
                else if (led == 1){
                    led = 2;
                }
                else if (led == 2){
                    led = 0;
                }
                turnOnLED(led);
                IFS0bits.T1IF = 0;
                nextstate = WP;
                T1CONbits.TON = 0;
                
                break;
                
                
                
        //////////////////////DOWNWARD///////////////  
                
                
                //////////////////////UPWARD///////////////  
                
            case ledup:
                
                
                
                if(led == 0){
                    led = 2;
                }
                else if (led == 1){
                    led = 0;
                }
                else if (led == 2){
                    led = 1;
                }
                turnOnLED(led);
                IFS0bits.T1IF = 0;
                nextstate = WP;
                T1CONbits.TON = 0;
                
                break;
                
                
                
        //////////////////////UPWARD///////////////
                
                
        
                
       }
        
    }
    
 //////////////////////////////////PART3////////////////////////////////////   
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0;
}

   //////////////////////////////////PART2////////////////////////////////////
//    while(1){
//        
//        switch(nextstate){
//            
//            initTimer1();
//            
//           case led1:
//               
//               nextstate = led2;
//               turnOnLED1(1);
//               
//               delayonesecondTimer();
//              
//                break;
//                
//           case led2:
//              
//                nextstate = led3;    
//                turnOnLED2(1);
//                
//                delayonesecondTimer();
//             
//                break;
//              
//           case led3:
//              
//               nextstate = led1;
//               turnOnLED3(1);
//               
//               delayonesecondTimer();
//               
//                break; 
//           
//       }
//        
//    }
 //////////////////////////////////PART2////////////////////////////////////

//           case led1down:
//               if (PORTDbits.RD6 == PRESSED){
//                    
//                    nextstate = DP2;
//               
//                }
//               
//               nextstate = led2down;
//               turnOnLED1(1);
//               
//               delayonesecondTimer();
//               
//               
//              
//                break;
//                
//           case led2down:
//               if (PORTDbits.RD6 == PRESSED){
//                    
//                    nextstate = DP2;
//                
//                }
//              
//                nextstate = led3down;    
//                turnOnLED2(1);
//                
//                delayonesecondTimer();
//                
//               
//             
//                break;
//              
//           case led3down:
//               if (PORTDbits.RD6 == PRESSED){
//                    
//                    nextstate = DP2;
//                
//                }
//              
//               nextstate = led1down;
//               turnOnLED3(1);
//               
//               delayonesecondTimer();
//               
//              
//               
//                break; 
        //////////////////////DOWNWARD///////////////
                
        //////////////////////UPWARD///////////////     
//           case led1up:
//               if (PORTDbits.RD6 == RELEASED){
//                    
//                    nextstate = led2down;
//                
//                }
//               
//               nextstate = led3up;
//               turnOnLED1(1);
//               
//               delayonesecondTimer();
//              
//                break;
//                
//           case led3up:
//               if (PORTDbits.RD6 == RELEASED){
//                    
//                    nextstate = led1down;
//                
//                }
//              
//                nextstate = led2up;    
//                turnOnLED3(1);
//                
//                delayonesecondTimer();
//             
//                break;
//              
//           case led2up:
//               if (PORTDbits.RD6 == RELEASED){
//                    
//                    nextstate = led3down;
//                
//                }
//              
//               nextstate = led1up;
//               turnOnLED2(1);
//               
//               delayonesecondTimer();
//               
//                break; 
        //////////////////////UPWARD///////////////

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed