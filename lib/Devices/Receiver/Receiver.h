#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "stdint.h"

#include "Arduino.h"

#include "Device.h"

#define RX_BAUD_RATE        (100000)
#define RX_USART_CONFIG     SERIAL_8E2_RXINV_TXINV

class Receiver: private Device {

    private:
        float data[8];
        uint8_t rx_pin;
        uint8_t tx_pin;
        HardwareSerial *serial;
        bool connected;

    public:
        Receiver(uint8_t rx_pin, uint8_t tx_pin, HardwareSerial *serial);
        void setup();   // Inherited from Device
        void loop();    // Inherited from Device
        void close();   // Inherited from Device
        float getData(uint8_t channel); // Reads the value for a channel
        bool isConnected();


}

#endif // __RECEIVER_H__