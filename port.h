/*这个文件主要是抽象向PIC写入操作*/

#ifndef __PORT_H__
#define __PORT_H__

#include "types.h"

class port{
protected:
    uint16_t portnumber; 
    port(uint16_t portnumber);
    ~port();
};

class port8bit : public port{
public:
    port8bit(uint16_t potrnumber);
    ~port8bit();
    virtual void write(uint8_t data); //write data
    virtual uint8_t read(); //read data
};

class port8bitslow : public port{
public:
    port8bitslow(uint16_t potrnumber);
    ~port8bitslow();
    void write(uint8_t data); //write data
    uint8_t read(); //read data
};

class port16bit : public port{
public:
    port16bit(uint16_t potrnumber);
    ~port16bit();
    virtual void write(uint16_t data); //write data
    virtual uint16_t read(); //read data
};

class port32bit : public port{
public:
    port32bit(uint16_t potrnumber);
    ~port32bit();
    virtual void write(uint32_t data); //write data
    virtual uint32_t read(); //read data
};
#endif