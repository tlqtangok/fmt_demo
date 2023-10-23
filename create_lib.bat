set VS_CL_OPT_NODEBUG=/c /ZI /nologo /W3 /WX- /diagnostics:column /sdl /O2 /Oi /D NDEBUG /D _CONSOLE /D _UNICODE /D UNICODE /Gm- /EHsc /MDd /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /permissive-  /external:W3 /Gd /TP /FC /errorReport:prompt
set VS_CL_OPT_DEBUG=/c /ZI /JMC /nologo /W3 /WX- /diagnostics:column /sdl /O2 /D DEBUG /D _CONSOLE /D _UNICODE /D UNICODE /Gm- /EHsc /MDd /GS /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /permissive-  /external:W3 /Gd /TP /FC /errorReport:prompt

::set VS_CL_OPT_NODEBUG=/c /Zi /nologo /W3 /WX- /diagnostics:column /sdl /O2 /Oi /GL /D NDEBUG /D _CONSOLE /D _UNICODE /D UNICODE /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /permissive-  /external:W3 /Gd /TP /FC /errorReport:prompt

set VS_LIB_OPT=/NOLOGO /MACHINE:X64

set VS_LINK_OPT_DEBUG=/ERRORREPORT:PROMPT  /INCREMENTAL /MANIFEST  /manifest:embed /DEBUG /SUBSYSTEM:CONSOLE /TLBID:1 /DYNAMICBASE /NXCOMPAT /MACHINE:X64 /MANIFESTUAC:"level='asInvoker' uiAccess='false'"


set INC=%CD%\_3rd\fmt-master\include
set SRC=%CD%\_3rd\fmt-master\src

@echo off
where cl.exe 
if not %errorlevel% equ 0 (
    echo "- please setup your vs2022 environment"
    exit /b -1
)
@echo on

del *.obj *.lib *.dll vc140.* mainapp.* *.o

CL.exe  %VS_CL_OPT_DEBUG%   /I"%INC%"  main.cpp

CL.exe  %VS_CL_OPT_NODEBUG% /I"%INC%" %SRC%\format.cc %SRC%\os.cc
lib.exe %VS_LIB_OPT% /OUT:"slib.lib"  format.obj  os.obj 

link.exe %VS_LINK_OPT_DEBUG% /implib:"slib.lib" /out:"mainapp.exe"  main.obj slib.lib
.\mainapp.exe
