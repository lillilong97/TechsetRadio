#include "mbed.h"
#include "PinDetect.h"
#include "buttons.h"
#include "digipot.h"
//potentiometer enumeration 
#define MONO_P 1 
#define ST_R_P 2
#define ST_L_P 3
//gain enumeration
//128 should be 50% of R, 128/256
#define ST_R_G 64
#define ST_L_G 64
#define MONO_G 64

#define LEFT 1
#define RIGHT 2

DigitalOut LED_1(LED1);


// PWREN
DigitalOut PWREN_R(p22);
DigitalOut PWREN_L(p23);


//test pin\

volatile bool LED = 0;
//volatile float value;
/*
//CTS
DigitalIn RTS(p25);
DigitalOut CTS(p26);
*/

//Sends char command to RN-52;



void setgain(int circuit_pot, int level) {
    switch(circuit_pot) {
        case MONO_P:
            write_wip(0x00,level,2);
            break;
        case ST_R_P:
            write_wip(0x00,level,1);
            break;
        case ST_L_P:
            write_wip(0x10,level,1);
            break;

    }
            
    
}

void left_up(void) {
    buttons = buttons | LBUP;
    LED =1;
}

void left_mid(void) {
    buttons = buttons | LBM;
    LED = 1;
}

void left_down(void) {
    buttons = buttons | LBDN;
    LED = 1;
}

void right_up(void) {
    buttons = buttons | RBUP;
    LED = 1;
}

void right_mid(void) {
    buttons = buttons | RBM;
    LED = 1;
}

void right_down(void) {
    buttons = buttons | RBDN;
    LED =1;
}


int main() {
    PWREN_L = 1;
    PWREN_R = 1;
    M_S = 0;
   // pc.baud(115200);
   rn52_left.baud(115200);
   rn52_right.baud(115200);
    L_UP.mode(PullUp);
    L_MID.mode(PullUp);
    L_DN.mode(PullUp);

    R_UP.mode(PullUp);
    R_MID.mode(PullUp);
    R_DN.mode(PullUp);

    wait(0.01); 
   
    L_UP.attach_deasserted(&left_up);
    L_MID.attach_deasserted(&left_mid);
    L_DN.attach_deasserted(&left_down);

    R_UP.attach_deasserted(&right_up);
    R_MID.attach_deasserted(&right_mid);
    R_DN.attach_deasserted(&right_down);
    
    L_UP.setSampleFrequency();
    L_MID.setSampleFrequency();
    L_DN.setSampleFrequency();
    R_UP.setSampleFrequency();
    R_MID.setSampleFrequency();
    R_DN.setSampleFrequency();
    
    pot1.format(8,0); //sets 8 bit data format and mode 0 
    // mode chosen somewhat arbitrarily
    setgain(MONO_P,MONO_G);
    setgain(ST_R_P,ST_R_G);
    setgain(ST_L_P,ST_L_G);

    int count = 0;
    //send_buff("+\r\n",RIGHT);
    
    while(1) {
            
            wait(0.05);
            state = set_state(buttons,state); 
            
            if(LED) {
                LED_1 = 1;
            } else {
                LED_1 = 0;
            }
            if(count == 50) {
                //pc.printf("state: %d\n",state);
                button_actions(buttons,state);
                count =  0;
                buttons = OFF;
                state = OFF;
                LED = 0;
            }
            
            count++;
            

    }
}
