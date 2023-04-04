#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0, 0, 0),
unusedSegmentSeletor(0, 0, 0),
codeSegmentSelector(0, 64*1024*1024, 0x9A),  //0x9a代表kernel mode code segment
dataSegmentSeletor(0, 64*1024*1024, 0x92){  //0下2代表kernel mode data segment
    uint32_t i[2];
    i[0] = (uint32_t)this; //这个对象的起使指针
    i[1] = sizeof(GlobalDescriptorTable) << 16;

    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i)+2));
}

GlobalDescriptorTable::~GlobalDescriptorTable(){

}

uint16_t GlobalDescriptorTable::DataSegmentSelector(){
    return (uint8_t*)&dataSegmentSeletor - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector(){
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags){
    uint8_t* target = (uint8_t*)this;

    if(limit <= 65536){
        target[6] = 0x40; //将flags和hight limit设置成0x40
    }else{
        if((limit & 0xFFF) != 0xFFF) limit = (limit >> 12) - 1;
        else limit = limit >> 12;
        target[6] = 0xC;
    }   

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF; 

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    target[5] = flags;
}    

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base(){
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit(){
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[6] & 0xF;
    result = (result << 8) + target[1]; 
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0) result = (result << 12) | 0xFFF;

    return result;    
}