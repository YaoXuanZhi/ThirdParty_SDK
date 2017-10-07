#��makefile�ļ���AutoNMaker�Զ�����
##########################��������ʽ��makefile���##########################
#�����������ɵĿ�ִ���ļ�����
ProjName=worm

#���ú�׺��
ExtName=.exe

#���ù���Ŀ¼
WorkDir=$(MAKEDIR)/

#���õ�ǰ������Դ�ļ�������·��
ResNames=$(OutputDir)/pdcurses.res 

#ͨ�õ�RC��Դ�ļ������������Ϣ
RSCConfig=/l 0x804 /d "NDEBUG"

#���õ�ǰ����Ŀ���ļ�������·��
ObjNames=$(OutputDir)\addch.obj $(OutputDir)\addchstr.obj $(OutputDir)\addstr.obj $(OutputDir)\attr.obj $(OutputDir)\beep.obj $(OutputDir)\bkgd.obj $(OutputDir)\border.obj $(OutputDir)\clear.obj $(OutputDir)\color.obj $(OutputDir)\debug.obj $(OutputDir)\delch.obj $(OutputDir)\deleteln.obj $(OutputDir)\deprec.obj $(OutputDir)\getch.obj $(OutputDir)\getstr.obj $(OutputDir)\getyx.obj $(OutputDir)\inch.obj $(OutputDir)\inchstr.obj $(OutputDir)\initscr.obj $(OutputDir)\inopts.obj $(OutputDir)\insch.obj $(OutputDir)\insstr.obj $(OutputDir)\instr.obj $(OutputDir)\kernel.obj $(OutputDir)\keyname.obj $(OutputDir)\mouse.obj $(OutputDir)\move.obj $(OutputDir)\outopts.obj $(OutputDir)\overlay.obj $(OutputDir)\pad.obj $(OutputDir)\panel.obj $(OutputDir)\printw.obj $(OutputDir)\refresh.obj $(OutputDir)\scanw.obj $(OutputDir)\scr_dump.obj $(OutputDir)\scroll.obj $(OutputDir)\slk.obj $(OutputDir)\termattr.obj $(OutputDir)\terminfo.obj $(OutputDir)\touch.obj $(OutputDir)\util.obj $(OutputDir)\window.obj $(OutputDir)\pdcclip.obj $(OutputDir)\pdcdisp.obj $(OutputDir)\pdcgetsc.obj $(OutputDir)\pdckbd.obj $(OutputDir)\pdcscrn.obj $(OutputDir)\pdcsetsc.obj $(OutputDir)\pdcutil.obj $(OutputDir)\$(ProjName).obj 

#�������Ŀ¼
OutputDir=Out

#���ɶ������ļ�֮�������ʱ�ļ�
All:buildOutputDir $(ProjName) clean

#�����Ҫ����LIB�ĵط�����Щ����£���Ҫʹ��htmlhelp.lib
AdditLibs=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#������ϵͳ���ͣ�WINDOWS��CONSOLE
SubSysType=CONSOLE

#ͨ�õ�link.exe��������Ϣ
LinkConfig=/nologo /subsystem:$(SubSysType) /incremental:no

#ͨ�õ�lib.exe��������Ϣ
LibConfig=/nologo /ltcg

#���ô������Դ�ļ�
ObjFiles=$(ResNames) $(ObjNames) \
!IFDEF PRECOMPILE
$(OutputDir)\$(PRECOMPILE).obj
!ENDIF

#����Ŀ���ļ�
$(ProjName):cppCompileStep rcCompileStep
    @echo ����Ŀ���ļ�
!IFDEF COMPLIESTATICLIB
    lib.exe $(ObjFiles) $(LibConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ELSE
    Link.exe $(ObjFiles) $(AdditLibs) $(LinkConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ENDIF

#�����ַ�����UNICODE��MBCS
CharSetType=UNICODE

#ͨ�õı���Դ�ļ���������Ϣ��ע�⣬��VC6.0�У���û��֧��/Zc:wchar_tŶ
CLConfig=/MT /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_$(SubSysType)" /D "_$(CharSetType)" /D "$(CharSetType)" -Fo"$(OutputDir)/" /INCREMENTAL:NO

#���ø��Ӱ���Ŀ¼
INCLUDE=$(INCLUDE);../include;%(AdditionalIncludeDirectories);

#�½�Ŀ���ļ����Ŀ¼
buildOutputDir:
  if not exist "$(OutputDir)" mkdir "$(OutputDir)"

#���ô������Դ�ļ�
CppFiles="$(WorkDir)..\lib\src\addch.c" "$(WorkDir)..\lib\src\addchstr.c" "$(WorkDir)..\lib\src\addstr.c" "$(WorkDir)..\lib\src\attr.c" "$(WorkDir)..\lib\src\beep.c" "$(WorkDir)..\lib\src\bkgd.c" "$(WorkDir)..\lib\src\border.c" "$(WorkDir)..\lib\src\clear.c" "$(WorkDir)..\lib\src\color.c" "$(WorkDir)..\lib\src\debug.c" "$(WorkDir)..\lib\src\delch.c" "$(WorkDir)..\lib\src\deleteln.c" "$(WorkDir)..\lib\src\deprec.c" "$(WorkDir)..\lib\src\getch.c" "$(WorkDir)..\lib\src\getstr.c" "$(WorkDir)..\lib\src\getyx.c" "$(WorkDir)..\lib\src\inch.c" "$(WorkDir)..\lib\src\inchstr.c" "$(WorkDir)..\lib\src\initscr.c" "$(WorkDir)..\lib\src\inopts.c" "$(WorkDir)..\lib\src\insch.c" "$(WorkDir)..\lib\src\insstr.c" "$(WorkDir)..\lib\src\instr.c" "$(WorkDir)..\lib\src\kernel.c" "$(WorkDir)..\lib\src\keyname.c" "$(WorkDir)..\lib\src\mouse.c" "$(WorkDir)..\lib\src\move.c" "$(WorkDir)..\lib\src\outopts.c" "$(WorkDir)..\lib\src\overlay.c" "$(WorkDir)..\lib\src\pad.c" "$(WorkDir)..\lib\src\panel.c" "$(WorkDir)..\lib\src\printw.c" "$(WorkDir)..\lib\src\refresh.c" "$(WorkDir)..\lib\src\scanw.c" "$(WorkDir)..\lib\src\scr_dump.c" "$(WorkDir)..\lib\src\scroll.c" "$(WorkDir)..\lib\src\slk.c" "$(WorkDir)..\lib\src\termattr.c" "$(WorkDir)..\lib\src\terminfo.c" "$(WorkDir)..\lib\src\touch.c" "$(WorkDir)..\lib\src\util.c" "$(WorkDir)..\lib\src\window.c" "$(WorkDir)..\lib\win32\pdcclip.c" "$(WorkDir)..\lib\win32\pdcdisp.c" "$(WorkDir)..\lib\win32\pdcgetsc.c" "$(WorkDir)..\lib\win32\pdckbd.c" "$(WorkDir)..\lib\win32\pdcscrn.c" "$(WorkDir)..\lib\win32\pdcsetsc.c" "$(WorkDir)..\lib\win32\pdcutil.c" "$(WorkDir)..\demos\$(ProjName).c" 

#����Դ�ļ�
!IFDEF PRECOMPILE
cppCompileStep:
    @echo ����Դ�ļ�
    cl.exe $(CLConfig) -Yc"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" $(PRECOMPILE).cpp
    cl.exe $(CLConfig) -Yu"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" $(CppFiles)
!ELSE
cppCompileStep:
    @echo ����Դ�ļ�
    cl.exe $(CLConfig) $(CppFiles)
!ENDIF

#������Դ�ļ�
rcCompileStep:
    rc.exe $(RSCConfig) -Fo"$(OutputDir)/pdcurses.res" $(WorkDir)..\lib\win32\pdcurses.rc 


#����м��ļ�
clean:
    @echo ִ����ɣ�������O(��_��)O����~
##########################��������ʽ��makefile���##########################
