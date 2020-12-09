Serial pc(USBTX,USBRX);
//button states
#define LBUP 0b000001       //left up
#define LBM  0b000010       //left mid
#define LBDN 0b000100       //left down
#define RBUP 0b001000       //right up
#define RBM  0b010000       //right mid
#define RBDN 0b100000       //right down
#define LSKF 0b000011       //LBUP | LBM     //left skip forward
#define RSKF 0b011000       //RBUP | RBM     //right skip forward
#define LSKB 0b000110       //LBDN | LBM     //left skip back
#define RSKB 0b110000       //RBDN | RBM     //right skip back
#define OFF  0b000000
#define MS_C 0b010010       //LBM | RBM      //toggle mono or stereo mode
#define LEFT 1
#define RIGHT 2

// RN-52 Serial Object
Serial rn52_right(p9,p10);
Serial rn52_left(p28,p27);

volatile int state = OFF;
volatile int buttons = 0b00;

PinDetect L_UP(p17);
PinDetect L_MID(p18);
PinDetect L_DN(p19);

PinDetect R_UP(p14);
PinDetect R_MID(p15);
PinDetect R_DN(p16);

//Mono Stereo Toggle Pin
DigitalOut M_S(p24);


//ascii commands
char play[] = "AP\r\n";
char vol_up[] = "AV+\r\n";
char vol_dn[] = "AV-\r\n";
char next[] = "AT+\r\n";
char last[] = "AT-\r\n";
char accept_call[] = "C\r\n";
char reject_call[] = "E\r\n";

void send_buff (char *buff,int L_R) {
    for(int i = 0; i < sizeof(buff); i++) {
        if(L_R == LEFT) {
            rn52_left.putc(buff[i]);
        } else if(L_R == RIGHT) {
            rn52_right.putc(buff[i]);
        }
    
    }
    
    
}

int set_state(int buttons, int state) {
    
    if(buttons == LBUP) {
        state = LBUP; 
    } else if(buttons == LBM) {
        state = LBM;
    } else if(buttons == LBDN) {
        state = LBDN;
    } else if(buttons == RBUP) {
        state = RBUP;
    } else if(buttons == RBM) {
        state = RBM;
    } else if(buttons == RBDN) {
        state = RBDN;
    } else if(buttons == LSKF) {
        state = LSKF;
    } else if(buttons == RSKF) {
        state = RSKF;
    } else if(buttons == LSKB) {
        state = LSKB;
    } else if(buttons == RSKB) {
        state = RSKB;
    } else if (buttons == OFF) {
        state = OFF;
    } else if (buttons == MS_C) {
        state = MS_C;
    }



    return state;
    
    }
    

void button_actions(int buttons, int state) {

     if(state == LBUP) {
        send_buff(vol_up,LEFT);
        state = OFF;
   } else if(state == LBM) {
        send_buff(play,LEFT);
        state = OFF;
   } else if(state == LBDN) {
        send_buff(vol_dn,LEFT);
        state = OFF;
   } else if(state == RBUP) {
        send_buff(vol_up,RIGHT);
        state = OFF;
   } else if(state == RBM) {
        send_buff(play,RIGHT);
        state = OFF;
   } else if(state == RBDN) {
        send_buff(vol_dn,RIGHT);
        state = OFF;
   } else if(state == LSKF) {
        send_buff(next,LEFT);
        state = OFF;
   } else if(state == RSKF) {
        send_buff(next,RIGHT);
        state = OFF;
   } else if(state == RSKB) {
        send_buff(last,RIGHT);
        state = OFF;
   } else if(state == LSKB) {
        send_buff(last,LEFT);
        state = OFF;
   } else if(state == MS_C) {
        M_S = !M_S;
        state = OFF; 
   } else if (state == OFF) {
       state = OFF;
    }
   
}
