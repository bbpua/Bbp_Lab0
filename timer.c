/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#include <proc/p32mx470f512l.h>

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // .5 seconds. Enable its interrupt
    
    
    TMR1 = 0;
    PR1 = 39062; // 1 SECOND
    
    T1CONbits.TCKPS = 3; //PRESCALAR 256
    T1CONbits.TCS = 0;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    IPC1bits.T1IP = 7;
    T1CONbits.ON = 1;
    
}


void delayonesecondTimer(){

    TMR2 = 0;
    PR2 = 39062;
    
    T2CONbits.TCKPS = 7; //PRESCALAR OF 256
    T2CONbits.ON = 1; //WILL TURN ON TIMER
    
    while (IFS0bits.T2IF == 0); //STAY UNTIL TIMER IS DONE 
    
    IFS0bits.T2IF = 0; //PUT DOWN THE FLAG
    T2CONbits.ON = 0; //TURN OFF THE TIMER




}

void halfsecondTimer(){

    TMR3 = 0;
    PR3 = 19531; // .5 SECOND
    
    T1CONbits.TCKPS = 3; //PRESCALAR 256
    T1CONbits.TCS = 0;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    IPC1bits.T1IP = 7; 
    T1CONbits.ON = 1;


}