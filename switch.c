/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include "switch.h"
#include <xc.h>
#include <proc/p32mx470f512l.h>

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1 
#define DISABLED 0

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;
    CNPUDbits.CNPUD6 = ENABLED;
}


/* *****************************************************************************
 End of File
 */
