0x -> Tell C compiler hex number
0xFFFF0000 -> needs 32 bits, obviously

Eeach hex digit -> 0...16, or 0...2^4,
thus needing 4 bits.
We have 8 * 4 = 32
 
FF: alpha
FF: red
00: green
00: blue

ColorBuffer for each pixel

sizeof(int) -> depends, yeah ok 4 bytes

uint8_t  
usigned int of 8 bits

uint32_t* color_buffer 
Pointer?

Pointer to first position of the address

uint32_t* color_buffer = NULL;

void setup(void) {
    color_buffer = (uint32__t*) malloc(sizeof(uint32_t) * window_width * window_height); 
}

    printf("%zu\n", sizeof(uint32_t)); //4
    printf("%zu\n", sizeof(uint16_t)); //2
    printf("%zu\n", sizeof(uint8_t)); //1