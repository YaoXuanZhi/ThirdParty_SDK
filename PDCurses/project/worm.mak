#本makefile文件由AutoNMaker自动生成
##########################下面是正式的makefile语句##########################
#设置最终生成的可执行文件名称
ProjName=worm

#设置后缀名
ExtName=.exe

#设置工作目录
WorkDir=$(MAKEDIR)/

#设置当前所有资源文件的所在路径
ResNames=$(OutputDir)/pdcurses.res 

#通用的RC资源文件编译的设置信息
RSCConfig=/l 0x804 /d "NDEBUG"

#设置当前所有目标文件的所在路径
ObjNames=$(OutputDir)\addch.obj $(OutputDir)\addchstr.obj $(OutputDir)\addstr.obj $(OutputDir)\attr.obj $(OutputDir)\beep.obj $(OutputDir)\bkgd.obj $(OutputDir)\border.obj $(OutputDir)\clear.obj $(OutputDir)\color.obj $(OutputDir)\debug.obj $(OutputDir)\delch.obj $(OutputDir)\deleteln.obj $(OutputDir)\deprec.obj $(OutputDir)\getch.obj $(OutputDir)\getstr.obj $(OutputDir)\getyx.obj $(OutputDir)\inch.obj $(OutputDir)\inchstr.obj $(OutputDir)\initscr.obj $(OutputDir)\inopts.obj $(OutputDir)\insch.obj $(OutputDir)\insstr.obj $(OutputDir)\instr.obj $(OutputDir)\kernel.obj $(OutputDir)\keyname.obj $(OutputDir)\mouse.obj $(OutputDir)\move.obj $(OutputDir)\outopts.obj $(OutputDir)\overlay.obj $(OutputDir)\pad.obj $(OutputDir)\panel.obj $(OutputDir)\printw.obj $(OutputDir)\refresh.obj $(OutputDir)\scanw.obj $(OutputDir)\scr_dump.obj $(OutputDir)\scroll.obj $(OutputDir)\slk.obj $(OutputDir)\termattr.obj $(OutputDir)\terminfo.obj $(OutputDir)\touch.obj $(OutputDir)\util.obj $(OutputDir)\window.obj $(OutputDir)\pdcclip.obj $(OutputDir)\pdcdisp.obj $(OutputDir)\pdcgetsc.obj $(OutputDir)\pdckbd.obj $(OutputDir)\pdcscrn.obj $(OutputDir)\pdcsetsc.obj $(OutputDir)\pdcutil.obj $(OutputDir)\$(ProjName).obj 

#设置输出目录
OutputDir=Out

#生成二进制文件之后清除临时文件
All:buildOutputDir $(ProjName) clean

#填充需要连接LIB的地方，有些情况下，需要使用htmlhelp.lib
AdditLibs=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#设置子系统类型，WINDOWS或CONSOLE
SubSysType=CONSOLE

#通用的link.exe的配置信息
LinkConfig=/nologo /subsystem:$(SubSysType) /incremental:no

#通用的lib.exe的配置信息
LibConfig=/nologo /ltcg

#设置待编译的源文件
ObjFiles=$(ResNames) $(ObjNames) \
!IFDEF PRECOMPILE
$(OutputDir)\$(PRECOMPILE).obj
!ENDIF

#连接目标文件
$(ProjName):cppCompileStep rcCompileStep
    @echo 链接目标文件
!IFDEF COMPLIESTATICLIB
    lib.exe $(ObjFiles) $(LibConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ELSE
    Link.exe $(ObjFiles) $(AdditLibs) $(LinkConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ENDIF

#设置字符集：UNICODE或MBCS
CharSetType=UNICODE

#通用的编译源文件的设置信息，注意，在VC6.0中，还没有支持/Zc:wchar_t哦
CLConfig=/MT /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_$(SubSysType)" /D "_$(CharSetType)" /D "$(CharSetType)" -Fo"$(OutputDir)/" /INCREMENTAL:NO

#设置附加包含目录
INCLUDE=$(INCLUDE);../include;%(AdditionalIncludeDirectories);

#新建目标文件输出目录
buildOutputDir:
  if not exist "$(OutputDir)" mkdir "$(OutputDir)"

#设置待编译的源文件
CppFiles="$(WorkDir)..\lib\src\addch.c" "$(WorkDir)..\lib\src\addchstr.c" "$(WorkDir)..\lib\src\addstr.c" "$(WorkDir)..\lib\src\attr.c" "$(WorkDir)..\lib\src\beep.c" "$(WorkDir)..\lib\src\bkgd.c" "$(WorkDir)..\lib\src\border.c" "$(WorkDir)..\lib\src\clear.c" "$(WorkDir)..\lib\src\color.c" "$(WorkDir)..\lib\src\debug.c" "$(WorkDir)..\lib\src\delch.c" "$(WorkDir)..\lib\src\deleteln.c" "$(WorkDir)..\lib\src\deprec.c" "$(WorkDir)..\lib\src\getch.c" "$(WorkDir)..\lib\src\getstr.c" "$(WorkDir)..\lib\src\getyx.c" "$(WorkDir)..\lib\src\inch.c" "$(WorkDir)..\lib\src\inchstr.c" "$(WorkDir)..\lib\src\initscr.c" "$(WorkDir)..\lib\src\inopts.c" "$(WorkDir)..\lib\src\insch.c" "$(WorkDir)..\lib\src\insstr.c" "$(WorkDir)..\lib\src\instr.c" "$(WorkDir)..\lib\src\kernel.c" "$(WorkDir)..\lib\src\keyname.c" "$(WorkDir)..\lib\src\mouse.c" "$(WorkDir)..\lib\src\move.c" "$(WorkDir)..\lib\src\outopts.c" "$(WorkDir)..\lib\src\overlay.c" "$(WorkDir)..\lib\src\pad.c" "$(WorkDir)..\lib\src\panel.c" "$(WorkDir)..\lib\src\printw.c" "$(WorkDir)..\lib\src\refresh.c" "$(WorkDir)..\lib\src\scanw.c" "$(WorkDir)..\lib\src\scr_dump.c" "$(WorkDir)..\lib\src\scroll.c" "$(WorkDir)..\lib\src\slk.c" "$(WorkDir)..\lib\src\termattr.c" "$(WorkDir)..\lib\src\terminfo.c" "$(WorkDir)..\lib\src\touch.c" "$(WorkDir)..\lib\src\util.c" "$(WorkDir)..\lib\src\window.c" "$(WorkDir)..\lib\win32\pdcclip.c" "$(WorkDir)..\lib\win32\pdcdisp.c" "$(WorkDir)..\lib\win32\pdcgetsc.c" "$(WorkDir)..\lib\win32\pdckbd.c" "$(WorkDir)..\lib\win32\pdcscrn.c" "$(WorkDir)..\lib\win32\pdcsetsc.c" "$(WorkDir)..\lib\win32\pdcutil.c" "$(WorkDir)..\demos\$(ProjName).c" 

#编译源文件
!IFDEF PRECOMPILE
cppCompileStep:
    @echo 编译源文件
    cl.exe $(CLConfig) -Yc"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" $(PRECOMPILE).cpp
    cl.exe $(CLConfig) -Yu"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" $(CppFiles)
!ELSE
cppCompileStep:
    @echo 编译源文件
    cl.exe $(CLConfig) $(CppFiles)
!ENDIF

#编译资源文件
rcCompileStep:
    rc.exe $(RSCConfig) -Fo"$(OutputDir)/pdcurses.res" $(WorkDir)..\lib\win32\pdcurses.rc 


#清空中间文件
clean:
    @echo 执行完成，请验收O(∩_∩)O哈哈~
##########################上面是正式的makefile语句##########################
