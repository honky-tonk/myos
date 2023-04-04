#include "interrupts.h"

void printf(char * str);

InterruptManager::GateDescriptor  InterruptManager::InterruptDescriptorTable[256]; 

//constructor
InterruptManager::InterruptManager(GlobalDescriptorTable* gdt){
    uint16_t CodeSegment = gdt->CodeSegmentSelector();
    const uint8_t  IDT_INTERRUPT_GATE = 0xE; //0XE代表32bit interrupt gate

    //初始化256个IDT entry
    for(uint16_t i = 0; i < 256; i++) SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE); //初始化

    SetInterruptDescriptorTableEntry(0, CodeSegment, &interrput_handler_0, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(1, CodeSegment, &interrput_handler_1, 0, IDT_INTERRUPT_GATE);
}

InterruptManager::~InterruptManager(){}



void InterruptManager::SetInterruptDescriptorTableEntry(
        uint8_t interruptNumber,
        uint16_t codeSegmentSelectorOffset,
        void (*handler)(),  //传入handler指针
        uint8_t DescriptorPrivilegeLevlel,
        uint8_t DescriptorType
    ){
        const uint8_t IDT_PRESENT_BIT= 0x80; //因为是小端存储IDT高位的pbit必须置为1，而0x80为1000 0000，因为小端存储字节内部的bit也是小端，所以我们写1000 0000实际在cpu内部为0000 0001 
        InterruptDescriptorTable[interruptNumber].offset_low =  ((uint32_t)handler) & 0xffff;//32位系统这里只存储16个字节所以高位的16字节要mask掉
        InterruptDescriptorTable[interruptNumber].offset_high = ((uint32_t)handler) >> 16 & 0xffff; //将handler的低16位置为0，再右移16位
        InterruptDescriptorTable[interruptNumber].gdt_selector = codeSegmentSelectorOffset; //这里只能是code_segment，因为是指定中断处理函数
        InterruptDescriptorTable[interruptNumber].reserved = 0;
        InterruptDescriptorTable[interruptNumber].access = IDT_PRESENT_BIT | DescriptorType | ((DescriptorPrivilegeLevlel&3) << 5);
}

uint32_t InterruptManager::HandleInterrupt(uint8_t InterruptNumber, uint32_t esp){
    printf("INTERRUPT");
    return esp;
}