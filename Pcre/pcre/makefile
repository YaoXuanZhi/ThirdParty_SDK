##########################��������ʽ��makefile���##########################
#�����������ɵĿ�ִ���ļ�����
ProjName=pcre

#���ú�׺��
ExtName=.lib

#���õ�ǰ����Ŀ���ļ�������·��
ObjNames=$(OutputDir)\pcre_compile.obj $(OutputDir)\pcre_config.obj $(OutputDir)\pcre_dfa_exec.obj $(OutputDir)\pcre_exec.obj $(OutputDir)\pcre_fullinfo.obj $(OutputDir)\pcre_get.obj $(OutputDir)\pcre_globals.obj $(OutputDir)\pcre_info.obj $(OutputDir)\pcre_maketables.obj $(OutputDir)\pcre_newline.obj $(OutputDir)\pcre_ord2utf8.obj $(OutputDir)\pcre_refcount.obj $(OutputDir)\pcre_study.obj $(OutputDir)\pcre_tables.obj $(OutputDir)\pcre_try_flipped.obj $(OutputDir)\pcre_ucp_searchfuncs.obj $(OutputDir)\pcre_valid_utf8.obj $(OutputDir)\pcre_version.obj $(OutputDir)\pcre_xclass.obj $(OutputDir)\pcre_chartables.obj 

#�������Ŀ¼
OutputDir=Out

#���ɶ������ļ�֮�������ʱ�ļ�
All:buildOutputDir $(ProjName) clean

#������ϵͳ���ͣ�WINDOWS��CONSOLE
SubSysType=CONSOLE

#ͨ�õ����ӵ�������Ϣ
LibConfig=/nologo /subsystem:$(SubSysType)

#���ô������Դ�ļ�
ObjFiles= $(ObjNames) \
!IFDEF PRECOMPILE
$(OutputDir)\$(PRECOMPILE).obj
!ENDIF

#����Ŀ���ļ�
$(ProjName):cppCompileStep 
    @echo ����Ŀ���ļ�
    lib.exe $(ObjFiles) $(LibConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)

#�����ַ�����UNICODE��MBCS
CharSetType=UNICODE

#ͨ�õı���Դ�ļ���������Ϣ��ע�⣬��VC6.0�У���û��֧��/Zc:wchar_tŶ
CLConfig=/MT /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_$(SubSysType)" /D "_$(CharSetType)" /D "$(CharSetType)" -Fo"$(OutputDir)/" /INCREMENTAL:NO

#���ø��Ӱ���Ŀ¼
INCLUDE=$(INCLUDE);pcre-7.0;pcre-7.0-src;%(AdditionalIncludeDirectories);

#�½�Ŀ���ļ����Ŀ¼
buildOutputDir:
  if not exist "$(OutputDir)" mkdir "$(OutputDir)"

#���ô������Դ�ļ�
CppFiles=$(MAKEDIR)/pcre-7.0-src\pcre_compile.c $(MAKEDIR)/pcre-7.0-src\pcre_config.c $(MAKEDIR)/pcre-7.0-src\pcre_dfa_exec.c $(MAKEDIR)/pcre-7.0-src\pcre_exec.c $(MAKEDIR)/pcre-7.0-src\pcre_fullinfo.c $(MAKEDIR)/pcre-7.0-src\pcre_get.c $(MAKEDIR)/pcre-7.0-src\pcre_globals.c $(MAKEDIR)/pcre-7.0-src\pcre_info.c $(MAKEDIR)/pcre-7.0-src\pcre_maketables.c $(MAKEDIR)/pcre-7.0-src\pcre_newline.c $(MAKEDIR)/pcre-7.0-src\pcre_ord2utf8.c $(MAKEDIR)/pcre-7.0-src\pcre_refcount.c $(MAKEDIR)/pcre-7.0-src\pcre_study.c $(MAKEDIR)/pcre-7.0-src\pcre_tables.c $(MAKEDIR)/pcre-7.0-src\pcre_try_flipped.c $(MAKEDIR)/pcre-7.0-src\pcre_ucp_searchfuncs.c $(MAKEDIR)/pcre-7.0-src\pcre_valid_utf8.c $(MAKEDIR)/pcre-7.0-src\pcre_version.c $(MAKEDIR)/pcre-7.0-src\pcre_xclass.c $(MAKEDIR)/pcre-7.0\pcre_chartables.c 

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

#����м��ļ�
clean:
    @echo ִ����ɣ�������O(��_��)O����~
##########################��������ʽ��makefile���##########################