.text
.extern _ZN16InterruptManager15HandleInterruptEhj
.global _ZN16InterruptManager22IgnoreInterruptRequestEv #就是interrupt中的InterruptManager::IgnoreInterruptRequest()，这里是这个函数的实体


.macro interrput_handler num
.global _ZN16InterruptManager19interrput_handler_\num\()Ev #因为我们是cpp写的kernel，所以在cpp的class中写了成员函数，函数名字会被编译器魔改成其他格式...而我们这样写是为了cpp文件可以看到他
_ZN16InterruptManager19interrput_handler_\num\()Ev:
    movb $\num, (interruptnumber)
    jmp save_and_call
.endm

.macro exception_handler num
.global _ZN16InterruptManager19exception_handler_\num\()Ev
_ZN16InterruptManager19exception_handler_\num\()Evexception_handler_%1:
    movb $\num, (interruptnumber)
    jmp save_and_call
.endm

interrput_handler 0
interrput_handler 1
interrput_handler 2
interrput_handler 3
interrput_handler 4

save_and_call:
    pusha

    pushl %esp
    push (interruptnumber)
    call _ZN16InterruptManager15HandleInterruptEhj
    mov %eax, %esp 

    popa

_ZN16InterruptManager22IgnoreInterruptRequestEv:
    iret

.data
    interruptnumber: .byte 0 