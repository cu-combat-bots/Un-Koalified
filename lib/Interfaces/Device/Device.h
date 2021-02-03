#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Exceptions.h"

class Device
{
private:
    /* data */
public:
    Device();
    ~Device();

    void open(); // When a device is being loaded by the system, this method is called
    void loop(); // Once per loop, this method is called
    void close(); // When the device is being disconnected, this method is called
};


#endif // __DEVICE_H__