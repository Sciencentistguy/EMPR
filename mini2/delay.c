void delay(unsigned long tick) {
    for (unsigned long j = 0; j < tick; j++) {
        for (unsigned int i = 0; i < 0x10000; i++) {
            (void) 0;
        }
    }
}
