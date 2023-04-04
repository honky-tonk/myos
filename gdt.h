#ifndef __GDT_H__
#define __GDT_H__

#include "types.h"

class GlobalDescriptorTable{
public:
    class SegmentDescriptor{
    private:
        uint16_t limit_lo; //low limit
        uint16_t base_lo; //low base
        uint8_t  basehi;
        uint8_t type;
        uint8_t flags_limit_hi;
        uint8_t base_vhi;
    public:
        //constructor
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t Base();
        uint32_t Limit();
    }__attribute__((packed));

    //table entrys
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSeletor;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSeletor;
    
    // method
public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();
};

#endif