cmd_/home/admin/ics2023/nemu/build/obj-riscv32-nemu-interpreter/src/device/vga.o := unused

source_/home/admin/ics2023/nemu/build/obj-riscv32-nemu-interpreter/src/device/vga.o := src/device/vga.c

deps_/home/admin/ics2023/nemu/build/obj-riscv32-nemu-interpreter/src/device/vga.o := \
    $(wildcard include/config/vga/size/800x600.h) \
    $(wildcard include/config/target/am.h) \
    $(wildcard include/config/vga/show/screen.h) \
    $(wildcard include/config/vga/size/400x300.h) \
    $(wildcard include/config/has/port/io.h) \
    $(wildcard include/config/vga/ctl/port.h) \
    $(wildcard include/config/vga/ctl/mmio.h) \
    $(wildcard include/config/fb/addr.h) \
  /home/admin/ics2023/nemu/include/common.h \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
    $(wildcard include/config/isa64.h) \
  /home/admin/ics2023/nemu/include/macro.h \
  /home/admin/ics2023/nemu/include/debug.h \
  /home/admin/ics2023/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \
  /home/admin/ics2023/nemu/include/device/map.h \
  /home/admin/ics2023/nemu/include/cpu/difftest.h \
    $(wildcard include/config/difftest.h) \
  /home/admin/ics2023/nemu/include/difftest-def.h \
    $(wildcard include/config/isa/x86.h) \
    $(wildcard include/config/isa/mips32.h) \
    $(wildcard include/config/isa/riscv.h) \
    $(wildcard include/config/rv64.h) \
    $(wildcard include/config/rve.h) \
    $(wildcard include/config/isa/loongarch32r.h) \

/home/admin/ics2023/nemu/build/obj-riscv32-nemu-interpreter/src/device/vga.o: $(deps_/home/admin/ics2023/nemu/build/obj-riscv32-nemu-interpreter/src/device/vga.o)

$(deps_/home/admin/ics2023/nemu/build/obj-riscv32-nemu-interpreter/src/device/vga.o):
