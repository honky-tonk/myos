#include "port.h"

port::port(uint16_t portnumber){
    this->portnumber = portnumber;
}

port::~port(){

}

port8bit::port8bit(uint16_t portnumber)
:port(portnumber){

}

port8bit::~port8bit(){

}

void port8bit::write(uint8_t data){
    __asm__ volatile("outb %0, %1" : :/*input*/"a" (data),  "Nd" (portnumber)); //写入端口第一个是写入数据，第二个是端口
}

uint8_t port8bit::read(){
    uint8_t result; 
    __asm__ volatile("inb %1, %0":/*output*/ "=a"(result):/*input*/"Nd"(portnumber)); //在inline assembly的第二个optional选项中=代表只读，这里是从端口中读数据
    return result;
}

port8bitslow::port8bitslow(uint16_t portnumber)
:port(portnumber){

}

port8bitslow::~port8bitslow(){

}

void port8bitslow::write(uint8_t data){
    __asm__ volatile("outb %0, %1\n jmp 1f \n1: jmp 1f\n1:" : :/*input*/"a" (data),  "Nd" (portnumber)); //写入端口第一个是写入数据，第二个是端口
}




port16bit::port16bit(uint16_t portnumber)
:port(portnumber){

}

port16bit::~port16bit(){

}

void port16bit::write(uint16_t data){
    __asm__ volatile("outw %0, %1" : :/*input*/"a" (data),  "Nd" (portnumber)); //写入端口第一个是写入数据，第二个是端口,一个word 16bit
}

uint16_t port16bit::read(){
    uint16_t result; 
    __asm__ volatile("inw %1, %0":/*output*/ "=a"(result):/*input*/"Nd"(portnumber)); //在inline assembly的第二个optional选项中=代表只读，这里是从端口中读数据
    return result;
}

port32bit::port32bit(uint16_t portnumber)
:port(portnumber){

}

port32bit::~port32bit(){

}

void port32bit::write(uint32_t data){
    __asm__ volatile("outl %0, %1" : :/*input*/"a" (data),  "Nd" (portnumber)); //写入端口第一个是写入数据，第二个是端口
}

uint32_t port32bit::read(){
    uint32_t result; 
    __asm__ volatile("inl %1, %0":/*output*/ "=a"(result):/*input*/"Nd"(portnumber)); //在inline assembly的第二个optional选项中=代表只读，这里是从端口中读数据
    return result;
}

