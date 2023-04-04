#include "types.h"
#include "gdt.h"


extern void printf(const char* str){
    volatile char * videomemory = (volatile char*) 0xB8000;

    while( *str != '\0' ){
        *videomemory++ = *str++;
        *videomemory++ = 0xf0;
    }
}

extern "C" void KernelMain(){ //因为Cpp会把函数名改成XXX::KernelMain，所以我们特别指定按照C格式编译
    //*((int*)0xb8000)=0x07690748;
    printf("hello world!");
    
    GlobalDescriptorTable gdt;
    
    while(1);
}
