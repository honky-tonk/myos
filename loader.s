/* .开头的都是指示汇编器要干什么 */

/* 告诉汇编器我们要设置MAGIC因为不将MAGIC设置成固定值，grub不会认为他是内核,后面链接脚本会将他放在text的第一个位子让grub首先看到 */
/*.set MAGIC, 0xE85250D6 */ 
/*.set FLAGS, (1<<0 | 1 << 1)*/
/*.set CHECKSUM, -(MAGIC + FLAGS) */ 

/* XXX:表示label，注意他在内存中占位 */

.section .multiboot /* 设置multiboot头 */  
header_start:
    .long 0xE85250D6 /*magic number*/
    .long 0  /*protect mode*/
    .long header_end - header_start

    .long 0x100000000 - (0xE85250D6 + 0 + (header_end - header_start))  /*checksum*/

    /*end tag*/
    .short 0  /*type*/
    .short 0  /*flags*/
    .long 8  /*size*/

header_end:



.section .text      /* 写text段的指令 */
.extern KernelMain  /* extern指定外部函数，在使用的时候遍历所有文件找到他执行 */
.global loader

loader:
    mov $kernel_stack, %esp
    push %eax       /* 因为我们设置了multiboot，所以寄存器eax一般存储multiboot的指针，寄存器ebx存储magic number的指针 */
    push %ebx
    call KernelMain

_stop: /* 死循环，防止相面call完KernelMain后就退出 */
    cli             /* 禁止中断 */
    hlt             /* 暂停处理器*/
    jmp _stop       /* jump */

.section .bss
.space 2*1024*1024  /* 2Mib空间，因为当我们存东西进stack的时候是往前移动，所以我们要预留空间，不然容易发生覆写grub区域和firewall区域 */
kernel_stack:
