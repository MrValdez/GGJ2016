echo off
REM C -> ASM / S
..\..\snes-sdk\build\bin\816-tcc.exe -Wall -I../../snes-sdk/build/include -o snesc.ps -c snesc.c
pause

REM Optimize ASM files
python ..\..\snes-sdk\build\bin\816-opt.py snesc.ps > snesc.s

REM ASM -> OBJ
..\..\snes-sdk\build\bin\wla-65816.exe -io data.asm data.obj

..\..\snes-sdk\build\bin\wla-65816.exe -io snesc.s snesc.obj

REM OBJ -> SMC
..\..\snes-sdk\build\bin\wlalink.exe -dvSo data.obj snesc.obj input.obj init.obj graph.obj str.obj ggj2016.smc

call ggj2016.smc
