// 0x00 -- Wiper 0
// 0x01 -- Wiper 1
// 0x05 -- Status Register
// 0x40 = Midscale Wiper Value
// MCP4231 is 7-bits
// READ/WRITE 16-bits
// INCR/DECR 8-bits
/*
#define READ 0b11
#define WRITE 0b00
#define INCR 0b01
#define DECR 0b10
*/

#define W0 0x00
#define W1 0x10

SPI pot1(p5, p6, p7); // mosi, miso, sclk
//SPI pot2(p11,p12,p13);
DigitalOut cs_s(p30);
DigitalOut cs_m(p29);

void increment(int address,int chipnum) {
    if(chipnum == 1) {
        cs_s=1;
        cs_s=0;
        int cmd = address + 0x4;
        pot1.write(cmd);
        cs_s=1;
    } else if (chipnum == 2) {
        cs_m=1;
        cs_m=0;
        int cmd = address + 0x4;
        pot1.write(cmd);
        cs_m=1;
    }
}

void decrement(int address, int chipnum) {
    if(chipnum == 1) {
        cs_s=0;
        int cmd = address + 0x8;
        pot1.write(cmd);
        cs_s=1;
    } else if(chipnum ==2) {
        cs_m=0;
        int cmd = address + 0x8;
        pot1.write(cmd);
        cs_m=1;
    }

}


void write_wip(int address, int value, int chipnum) {
    if(chipnum == 1){
        cs_s=1;
        cs_s=0;
        pot1.write(address);
        pot1.write(value);
        cs_s=1;
    } else if(chipnum == 2) {
        cs_m=1;
        cs_m=0;
        pot1.write(address);
        pot1.write(value);
        cs_m=1;
    }
}

