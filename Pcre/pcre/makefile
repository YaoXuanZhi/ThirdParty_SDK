#本makefile文件由AutoNMaker自动生成
##########################下面是正式的makefile语句##########################
COMPLIESTATICLIB=1

#设置最终生成的可执行文件名称
ProjName=pcre

#设置后缀名
ExtName=.lib

#设置工作目录
WorkDir=$(MAKEDIR)/

#设置当前所有目标文件的所在路径
ObjNames=$(OutputDir)\pcre_compile.obj $(OutputDir)\pcre_config.obj $(OutputDir)\pcre_dfa_exec.obj $(OutputDir)\pcre_exec.obj $(OutputDir)\pcre_fullinfo.obj $(OutputDir)\pcre_get.obj $(OutputDir)\pcre_globals.obj $(OutputDir)\pcre_info.obj $(OutputDir)\pcre_maketables.obj $(OutputDir)\pcre_newline.obj $(OutputDir)\pcre_ord2utf8.obj $(OutputDir)\pcre_refcount.obj $(OutputDir)\pcre_study.obj $(OutputDir)\pcre_tables.obj $(OutputDir)\pcre_try_flipped.obj $(OutputDir)\pcre_ucp_searchfuncs.obj $(OutputDir)\pcre_valid_utf8.obj $(OutputDir)\pcre_version.obj $(OutputDir)\pcre_xclass.obj $(OutputDir)\pcre_chartables.obj 

#设置输出目录
OutputDir=Out

#生成二进制文件之后清除临时文件
All:buildOutputDir $(ProjName) final

#填充需要连接LIB的地方，有些情况下，需要使用htmlhelp.lib
AdditLibs=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#设置子系统类型，WINDOWS或CONSOLE
SubSysType=CONSOLE

#通用的link.exe的配置信息
LinkConfig=/nologo /subsystem:$(SubSysType) /incremental:no /debug

#通用的lib.exe的配置信息
LibConfig=/nologo /ltcg

#设置待编译的源文件
ObjFiles= $(ObjNames) \
!IFDEF PRECOMPILE
$(OutputDir)\$(PRECOMPILE).obj
!ENDIF

#连接目标文件
$(ProjName):cppCompileStep 
    @echo 链接目标文件
!IFDEF COMPLIESTATICLIB
    lib.exe $(ObjFiles) $(LibConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ELSE
    Link.exe $(ObjFiles) $(AdditLibs) $(LinkConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)
!ENDIF

#设置字符集：UNICODE或MBCS
CharSetType=UNICODE

#通用的编译源文件的设置信息，注意，在VC6.0中，还没有支持/Zc:wchar_t哦
CLConfig=/MT /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_CRT_SECURE_NO_WARNINGS" /D "_$(SubSysType)" /D "_$(CharSetType)" /D "$(CharSetType)" -Fo"$(OutputDir)/" /INCREMENTAL:NO

#设置附加包含目录
INCLUDE=$(INCLUDE);pcre-7.0;pcre-7.0-src;

#设置附加链接库目录
LIB=$(LIB);

#新建目标文件输出目录
buildOutputDir:
  if not exist "$(OutputDir)" mkdir "$(OutputDir)"

#设置待编译的源文件
CppFiles="$(WorkDir)pcre-7.0-src\pcre_compile.c" "$(WorkDir)pcre-7.0-src\pcre_config.c" "$(WorkDir)pcre-7.0-src\pcre_dfa_exec.c" "$(WorkDir)pcre-7.0-src\pcre_exec.c" "$(WorkDir)pcre-7.0-src\pcre_fullinfo.c" "$(WorkDir)pcre-7.0-src\pcre_get.c" "$(WorkDir)pcre-7.0-src\pcre_globals.c" "$(WorkDir)pcre-7.0-src\pcre_info.c" "$(WorkDir)pcre-7.0-src\pcre_maketables.c" "$(WorkDir)pcre-7.0-src\pcre_newline.c" "$(WorkDir)pcre-7.0-src\pcre_ord2utf8.c" "$(WorkDir)pcre-7.0-src\pcre_refcount.c" "$(WorkDir)pcre-7.0-src\pcre_study.c" "$(WorkDir)pcre-7.0-src\pcre_tables.c" "$(WorkDir)pcre-7.0-src\pcre_try_flipped.c" "$(WorkDir)pcre-7.0-src\pcre_ucp_searchfuncs.c" "$(WorkDir)pcre-7.0-src\pcre_valid_utf8.c" "$(WorkDir)pcre-7.0-src\pcre_version.c" "$(WorkDir)pcre-7.0-src\pcre_xclass.c" "$(WorkDir)pcre-7.0\pcre_chartables.c" 

#编译源文件
!IFDEF PRECOMPILE
cppCompileStep:
    @echo 编译源文件
    cl.exe $(CLConfig) -Yc"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" /Zi $(PRECOMPILE).cpp
    cl.exe $(CLConfig) -Yu"$(PRECOMPILE).h" -Fp"$(OutputDir)/$(ProjName).pch" /Zi $(CppFiles)
!ELSE
cppCompileStep:
    @echo 编译源文件
    cl.exe $(CLConfig) /Zi $(CppFiles)
!ENDIF

final:
    @echo 清空中间文件哦o(^▽^)o
    cd Out
    del *.obj *.lik *.log *.tlog *.res
    @echo 执行完成，请验收O(∩_∩)O哈哈~
##########################上面是正式的makefile语句##########################
