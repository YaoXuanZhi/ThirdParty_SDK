##########################下面是正式的makefile语句##########################
#设置最终生成的可执行文件名称
ProjName=pcre

#设置后缀名
ExtName=.lib

#设置当前所有目标文件的所在路径
ObjNames=$(OutputDir)\pcre_compile.obj $(OutputDir)\pcre_config.obj $(OutputDir)\pcre_dfa_exec.obj $(OutputDir)\pcre_exec.obj $(OutputDir)\pcre_fullinfo.obj $(OutputDir)\pcre_get.obj $(OutputDir)\pcre_globals.obj $(OutputDir)\pcre_info.obj $(OutputDir)\pcre_maketables.obj $(OutputDir)\pcre_newline.obj $(OutputDir)\pcre_ord2utf8.obj $(OutputDir)\pcre_refcount.obj $(OutputDir)\pcre_study.obj $(OutputDir)\pcre_tables.obj $(OutputDir)\pcre_try_flipped.obj $(OutputDir)\pcre_ucp_searchfuncs.obj $(OutputDir)\pcre_valid_utf8.obj $(OutputDir)\pcre_version.obj $(OutputDir)\pcre_xclass.obj $(OutputDir)\pcre_chartables.obj 

#设置输出目录
OutputDir=Out

#生成二进制文件之后清除临时文件
All:buildOutputDir $(ProjName) clean

#设置子系统类型，WINDOWS或CONSOLE
SubSysType=CONSOLE

#通用的链接的配置信息
LibConfig=/nologo /subsystem:$(SubSysType)

#设置待编译的源文件
ObjFiles= $(ObjNames) \
!IFDEF PRECOMPILE
$(OutputDir)\$(PRECOMPILE).obj
!ENDIF

#连接目标文件
$(ProjName):cppCompileStep 
    @echo 链接目标文件
    lib.exe $(ObjFiles) $(LibConfig) /OUT:$(OutputDir)/$(ProjName)$(ExtName)

#设置字符集：UNICODE或MBCS
CharSetType=UNICODE

#通用的编译源文件的设置信息，注意，在VC6.0中，还没有支持/Zc:wchar_t哦
CLConfig=/MT /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_$(SubSysType)" /D "_$(CharSetType)" /D "$(CharSetType)" -Fo"$(OutputDir)/" /INCREMENTAL:NO

#设置附加包含目录
INCLUDE=$(INCLUDE);pcre-7.0;pcre-7.0-src;%(AdditionalIncludeDirectories);

#新建目标文件输出目录
buildOutputDir:
  if not exist "$(OutputDir)" mkdir "$(OutputDir)"

#设置待编译的源文件
CppFiles=$(MAKEDIR)/pcre-7.0-src\pcre_compile.c $(MAKEDIR)/pcre-7.0-src\pcre_config.c $(MAKEDIR)/pcre-7.0-src\pcre_dfa_exec.c $(MAKEDIR)/pcre-7.0-src\pcre_exec.c $(MAKEDIR)/pcre-7.0-src\pcre_fullinfo.c $(MAKEDIR)/pcre-7.0-src\pcre_get.c $(MAKEDIR)/pcre-7.0-src\pcre_globals.c $(MAKEDIR)/pcre-7.0-src\pcre_info.c $(MAKEDIR)/pcre-7.0-src\pcre_maketables.c $(MAKEDIR)/pcre-7.0-src\pcre_newline.c $(MAKEDIR)/pcre-7.0-src\pcre_ord2utf8.c $(MAKEDIR)/pcre-7.0-src\pcre_refcount.c $(MAKEDIR)/pcre-7.0-src\pcre_study.c $(MAKEDIR)/pcre-7.0-src\pcre_tables.c $(MAKEDIR)/pcre-7.0-src\pcre_try_flipped.c $(MAKEDIR)/pcre-7.0-src\pcre_ucp_searchfuncs.c $(MAKEDIR)/pcre-7.0-src\pcre_valid_utf8.c $(MAKEDIR)/pcre-7.0-src\pcre_version.c $(MAKEDIR)/pcre-7.0-src\pcre_xclass.c $(MAKEDIR)/pcre-7.0\pcre_chartables.c 

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

#清空中间文件
clean:
    @echo 执行完成，请验收O(∩_∩)O哈哈~
##########################上面是正式的makefile语句##########################
