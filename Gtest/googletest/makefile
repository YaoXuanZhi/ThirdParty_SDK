#��makefile�ļ���AutoNMaker�Զ�����
##########################��������ʽ��makefile���##########################
COMPLIESTATICLIB=1

#�����������ɵĿ�ִ���ļ�����
ProjName=googletest

#���ú�׺��
ExtName=.lib

#���ù���Ŀ¼
WorkDir=$(MAKEDIR)/

#���õ�ǰ����Ŀ���ļ�������·��
ObjNames=$(OutputDir)\gtest_main.obj $(OutputDir)\gtest-all.obj 

#�������Ŀ¼
OutputDir=Out

#���ɶ������ļ�֮�������ʱ�ļ�
All:buildOutputDir $(ProjName) final

#�����Ҫ����LIB�ĵط�����Щ����£���Ҫʹ��htmlhelp.lib
AdditLibs=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#������ϵͳ���ͣ�WINDOWS��CONSOLE
SubSysType=CONSOLE

#ͨ�õ�link.exe��������Ϣ
LinkConfig=/nologo /subsystem:$(SubSysType) /incremental:no /debug

#ͨ�õ�lib.exe��������Ϣ
LibConfig=/nologo /ltcg /debug

#���ô������Դ�ļ�
ObjFiles= $(ObjNames) \
!IFDEF PRECOMPILE
$(OutputDir)\$(PRECOMPILE).obj
!ENDIF

#����Ŀ���ļ�
$(ProjName):cppCompileStep 
    @echo ����Ŀ���ļ�
!IFDEF COMPLIESTATICLIB
    lib.exe $(ObjFiles) $(LibConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ELSE
    Link.exe $(ObjFiles) $(AdditLibs) $(LinkConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ENDIF

#�����ַ�����UNICODE��MBCS
CharSetType=UNICODE

#ͨ�õı���Դ�ļ���������Ϣ��ע�⣬��VC6.0�У���û��֧��/Zc:wchar_tŶ
CLConfig=/MT /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_CRT_SECURE_NO_WARNINGS" /D "_$(SubSysType)" /D "_$(CharSetType)" /D "$(CharSetType)" -Fo"$(OutputDir)/" /INCREMENTAL:NO

#���ø��Ӱ���Ŀ¼
INCLUDE=$(INCLUDE);googletest-release-1.7.0;googletest-release-1.7.0\include;

#���ø������ӿ�Ŀ¼
LIB=$(LIB);

#�½�Ŀ���ļ����Ŀ¼
buildOutputDir:
  if not exist "$(OutputDir)" mkdir "$(OutputDir)"

#���ô������Դ�ļ�
CppFiles="$(WorkDir)googletest-release-1.7.0\src\gtest_main.cc" "$(WorkDir)googletest-release-1.7.0\src\gtest-all.cc" 

#����Դ�ļ�
!IFDEF PRECOMPILE
cppCompileStep:
    @echo ����Դ�ļ�
    cl.exe $(CLConfig) -Yc"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" /Zi $(PRECOMPILE).cpp
    cl.exe $(CLConfig) -Yu"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" /Zi $(CppFiles)
!ELSE
cppCompileStep:
    @echo ����Դ�ļ�
    cl.exe $(CLConfig) /Zi $(CppFiles)
!ENDIF

final:
    @echo ����м��ļ�Ŷo(^��^)o
    cd Out
    del *.obj *.lik *.log *.tlog *.res
    @echo ִ����ɣ�������O(��_��)O����~
##########################��������ʽ��makefile���##########################