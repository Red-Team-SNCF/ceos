CPPFLAGS := -fno-asynchronous-unwind-tables
CPPFLAGS += -fno-ident -fpack-struct=8 -falign-functions=1  
CPPFLAGS += -s -ffunction-sections -falign-jumps=1 -w 
CPPFLAGS += -falign-labels=1 -fPIC 
CPPFLAGS += -Wl,-s,--no-seh,--enable-stdcall-fixup,--gc-sections  -Wno-pointer-arith -fpermissive  -Os  -D MAIN_THREADED -e WinMain -lwinhttp -liphlpapi -lnetapi32 -mwindows 
#CPPFLAGS += -Wl,-s,--no-seh,--enable-stdcall-fixup,--gc-sections -fpermissive -e main -D_DEBUG -lwinhttp -liphlpapi -lnetapi32


CXX      := x86_64-w64-mingw32-g++
BUILD    := ./build

INCLUDE  := -I include
SRC      := source/*.cpp 
SRC      += ceos.cpp

all : exe dll

exe: clean
	@ echo "[*] Compiling x64 executable"
	@ mkdir -p build
	$(CXX) $(INCLUDE) $(SRC) $(EXE)  $(CPPFLAGS) -o build/ceos.exe 

dll: clean
	@ echo "[*] Compiling x64 DLL"
	@ mkdir build
	@ nasm -f win64 Source/ASM/rop.asm -o build/rop.o
	@ nasm -f win64 Source/ASM/win.asm -o build/win.o
	@ nasm -f win64 Source/ASM/syscallAsm.asm -o build/syscallAsm.o
	@ nasm -f win64 Source/ASM/stackSpoof.asm -o build/stackSpoof.o
	@ $(CXX) $(INCLUDE) $(SRC) $(DLL) -w build/rop.o build/win.o build/syscallAsm.o build/stackSpoof.o $(CPPFLAGS) -shared -e DllMain -o build/ra.dll -DDLL -D%SLEEP% -D%PROTOCOL% -D%SYSCALL% %SRDL% %CALLSTACK%

clean:
	@ rm -rf build/*.o
	@ rm -rf build/*.exe
	@ rm -rf build/*.dll

