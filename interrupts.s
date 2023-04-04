.text
.extern _ZN16InterruptManager15HandleInterruptEhj

.macro interrput_handler_%1
.global interrput_handler_%1
interrput_handler_%1:
    movb %1, (interruptnumber)
    jmp save_and_call
.endm

.macro exception_handler_%1
.global exception_handler_%1
exception_handler_%1:
    movb %1, (interruptnumber)
    jmp save_and_call
.endm

interrput_handler_0
interrput_handler_1

save_and_call:
    pusha

    pushl %esp
    push (interruptnumber)
    call _ZN16InterruptManager15HandleInterruptEhj
    mov %eax, %esp 

    popa
    iret

.data
    interruptnumber: . byte 0 