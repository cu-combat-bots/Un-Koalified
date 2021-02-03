#include "Receiver.h"

Receiver::Receiver(uint8_t rx_pin, uint8_t tx_pin, HardwareSerial serial) {
    this->serial = serial;
    this->rx_pin = rx_pin;
    this->tx_pin = tx_pin;
}

void Receiver::setup() {
    this->serial->setRX(this->rx_pin);
    this->serial->setTX(this->tx_pin);
    this->serial->begin(RX_BAUD_RATE, RX_USART_CONFIG);
}

void Receiver::loop() {
    // Want to read new data from the receiver
    // This data should be available from the serial port in SBUS format
    //  Byte[0]: Header = 0x0F
    //  Byte[1-22]: 16 servo channels, 11 bits/channel
    //      22 bytes * 8 bits/byte = 176 bits
    //      176 bits / 16 channels = 11 bits/channel
    //  Byte[23]: Digital Channels
    //      Bit 7: Digital Channel 17 (Mask 0x80)
    //      Bit 6: Digital Channel 18 (Mask 0x40)
    //      Bit 5: frame lost (0x20)
    //      Bit 4: failsafe activated (0x10)
    //  Byte[24]: SBUS End Byte = 0x00
    
    uint8_t data[25];
    uint8_t data_index = 0;
    memset(data, 0, 25);

    // Read a frame from the serial port
    while (data_index < 25) {
        while (!this->serial->available()); // Waiting for data to be avialable
        int byte = this->serial->read();

        bool is_first_byte = data_index == 0;
        bool is_start_frame = byte == 0x0F;
        if (is_first_byte && !is_start_frame) {
            continue;
        } else {
            data[data_index++] = byte;
        }
    }

    // Parse the data
    if (data[0] != 0x0F) { // Start Frame
        // throw new Exception
        return;
    }
    if (data[24] != 0x00) { // End Frame
        // throw new Exception
        return;
    }
    for (uint8_t i = 0; i < 16; i++) {
        uint8_t start_offset_bits = 8 + (11 * i);
        uint8_t start_offset_bytes = start_offset_bits / 8;
        uint8_t start_offset_remainder = start_offset_bits % 8;

        /**
         * Byte Index:     00 01 02 03 04 05 06 07 08 09 10 11  12 13 14 15 16 17 18 19 20 21 22
         * Channel Index: |------------- 0 -------------------||-------------- 1 ---------------|
         *                |------ Byte Offset ----||-Bit Offset-|
         */
        uint16_t raw = data[start_offset_bytes];
        raw = raw << start_offset_remainder;
        raw = raw >> 5;
        raw = raw & 0x3F; // Keep the bottom 11 bits

        this->data[i] = raw / 2047.0;
    }
}

void Receiver::close() {

}

float Receiver::getData(uint8_t channel) {

}

bool Receiver::isConnected() {

}