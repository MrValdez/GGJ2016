echo off
REM C -> ASM / S
snes-sdk\build\bin\816-tcc.exe -Wall -Isnes-sdk\build/include -o snesc.ps -c snesc.c
snes-sdk\build\bin\816-tcc.exe -Wall -Isnes-sdk\build/include -o input.ps -c input.c
snes-sdk\build\bin\816-tcc.exe -Wall -Isnes-sdk\build/include -o init.ps -c init.c
snes-sdk\build\bin\816-tcc.exe -Wall -Isnes-sdk\build/include -o graph.ps -c graph.c
snes-sdk\build\bin\816-tcc.exe -Wall -Isnes-sdk\build/include -o str.ps -c str.c

REM Optimize ASM files
python snes-sdk\build\bin\816-opt.py snesc.ps > snesc.s
python snes-sdk\build\bin\816-opt.py input.ps > input.s
python snes-sdk\build\bin\816-opt.py init.ps > init.s
python snes-sdk\build\bin\816-opt.py graph.ps > graph.s
python snes-sdk\build\bin\816-opt.py str.ps > str.s

REM ASM -> OBJ
snes-sdk\build\bin\wla-65816.exe -io data.asm data.obj

snes-sdk\build\bin\wla-65816.exe -io snesc.s snesc.obj
snes-sdk\build\bin\wla-65816.exe -io input.s input.obj
snes-sdk\build\bin\wla-65816.exe -io init.s init.obj
snes-sdk\build\bin\wla-65816.exe -io graph.s graph.obj
snes-sdk\build\bin\wla-65816.exe -io str.s str.obj

REM OBJ -> SMC
snes-sdk\build\bin\wlalink.exe -dvSo data.obj snesc.obj input.obj init.obj graph.obj str.obj snesc.smc

REM delete files
del *.ps
del *.s
del *.obj
del *.sym
