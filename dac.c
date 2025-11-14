#include <LPC214x.h>

// ===== DAC Initialization =====
void dac_init(void) {
    PINSEL1 = (PINSEL1 & ~(3 << 18)) | (2 << 18);  // P0.25 ? AOUT
}

// ===== Write 10-bit value to DAC =====
void analogWrite(unsigned int value) {
    DACR = (value & 0x3FF) << 6;   // 10-bit DAC value
}

// ===== Simple delay (approx 200 µs) =====
void delay_us(unsigned int us) {
    volatile unsigned int i;
    for (i = 0; i < us * 10; i++);
}

// ===== Main Program =====
int main(void) {
    int i;  // Changed to signed int
    dac_init();   // Initialize DAC
    
    while (1) {
        // Ramp UP (0 ? 1023)
        for (i = 0; i < 1024; i += 20) {  // Changed condition
            analogWrite(i);
            delay_us(200);
        }
        
        // Write max value to ensure full swing
        analogWrite(1023);
        delay_us(200);
        
        // Ramp DOWN (1023 ? 0)
        for (i = 1003; i >= 0; i -= 20) {  // Changed start and condition
            analogWrite(i);
            delay_us(200);
        }
        
        // Ensure it reaches 0
        analogWrite(0);
        delay_us(200);
    }
}