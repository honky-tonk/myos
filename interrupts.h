#ifndef __INTERRUPTS__
#define __INTERRUPTS__

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager{
protected:
    //IDT中的一个表项，一共64bit
    struct GateDescriptor{
        uint16_t offset_low;
        uint16_t gdt_selector;
        uint8_t reserved;
        uint8_t access;
        uint16_t offset_high;
    }__attribute__((packed));

    //IDT实体
    static GateDescriptor InterruptDescriptorTable[256];

    static void SetInterruptDescriptorTableEntry(
        uint8_t interruptNumber,
        uint16_t codeSegmentSelectorOffset,
        void (*handler)(),  //传入handler指针
        uint8_t DescriptorPrivilegeLevlel,
        uint8_t DescriptorType
    );

    struct InterruptDescriptorTablePointer{
        uint16_t size; //IDT size
        uint32_t base; //IDT start pointer
    };

public:
    InterruptManager(GlobalDescriptorTable* gdt);
    ~InterruptManager();

    /*
    *   本函数用于处理多个中断的通用函数
    *   当中断发生我们汇编会在栈中先放入error code(注意在中断发生的时候不会传入interrupt number到栈中，而是error code(我们第一个参数就是error_code)，我们只能通过error code去判断是什么中断再做处理)
    *   再放入esp也就是栈的指针，方便我们处理这个中断
    */
    
   void Activete();

    static uint32_t HandleInterrupt(uint8_t InterruptNumber, uint32_t esp);    
    
    static void IgnoreInterruptRequest(); //初始化IDT entry用的
    static void interrput_handler_0(); //处理error code为0的interrput，该函数由汇编(interrupts.s)调用,对应的label在汇编文件中由宏写出来了
    static void interrput_handler_1();
    static void interrput_handler_2();
    static void interrput_handler_3();
    static void interrput_handler_4();

};

#endif