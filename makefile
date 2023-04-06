#指定编译32位程序
GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions
# as是汇编器，指定汇编器生成可执行文件的位数
ASPARAMS = --32
#在链接的时候指定生成i386平台上的elf类型的可执行文件(elf也是unix下主要的可执行文件 macos貌似不支持)
LDPARAMS = -melf_i386

objects = loader.o gdt.o port.o interrupts.o kernel.o interruptstubs.o

%.o: %.cpp
# $@指定目标文件也就是.o结尾的文件 $<指定第一个依赖文件(第一个依赖的文件指的是冒号右边第一个文件) -c只做编译不做链接
	g++ $(GPPPARAMS) -o ./build/$@ -c $< 

%.o: %.s
	as $(ASPARAMS) -o ./build/$@ $<

#这个是由grub拿到内存中由cpu直接执行的可执行文件
kernel.bin: linker.ld $(objects) 
#链接	-T指定linke的script
# makefile每一行都会开一个新的shell执行,所以为保证cd和链接在一个shell中我们用&&连接起来
	cd ./build && ld $(LDPARAMS) -T  ../$< -o $@ $(objects) 

install: kernel.bin
	sudo cp ./build/$< isofiles/boot

isoimage:
	sudo grub-mkrescue -o my.iso isofiles

clean:
	rm -rf ./build/*.o ./build/kernel.bin