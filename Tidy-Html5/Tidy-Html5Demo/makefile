#本makefile文件由AutoNMaker自动生成
##########################下面是正式的makefile语句##########################
#设置最终生成的可执行文件名称
ProjName=Tidy-Html5Demo

#设置后缀名
ExtName=.exe

#设置工作目录
WorkDir=$(MAKEDIR)/

#设置当前所有目标文件的所在路径
ObjNames=$(OutputDir)\access.obj $(OutputDir)\alloc.obj $(OutputDir)\attrask.obj $(OutputDir)\attrdict.obj $(OutputDir)\attrget.obj $(OutputDir)\attrs.obj $(OutputDir)\buffio.obj $(OutputDir)\charsets.obj $(OutputDir)\clean.obj $(OutputDir)\config.obj $(OutputDir)\entities.obj $(OutputDir)\fileio.obj $(OutputDir)\gdoc.obj $(OutputDir)\iconvtc.obj $(OutputDir)\istack.obj $(OutputDir)\lexer.obj $(OutputDir)\localize.obj $(OutputDir)\mappedio.obj $(OutputDir)\parser.obj $(OutputDir)\pprint.obj $(OutputDir)\sprtf.obj $(OutputDir)\streamio.obj $(OutputDir)\tagask.obj $(OutputDir)\tags.obj $(OutputDir)\tidylib.obj $(OutputDir)\tmbstr.obj $(OutputDir)\utf8.obj $(OutputDir)\win32tc.obj $(OutputDir)\Tidy.obj 

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
INCLUDE=$(INCLUDE);Tidy-Html5\include;Tidy-Html5\src;

#设置附加链接库目录
LIB=$(LIB);

#新建目标文件输出目录
buildOutputDir:
  if not exist "$(OutputDir)" mkdir "$(OutputDir)"

#设置待编译的源文件
CppFiles="$(WorkDir)Tidy-Html5\src\access.c" "$(WorkDir)Tidy-Html5\src\alloc.c" "$(WorkDir)Tidy-Html5\src\attrask.c" "$(WorkDir)Tidy-Html5\src\attrdict.c" "$(WorkDir)Tidy-Html5\src\attrget.c" "$(WorkDir)Tidy-Html5\src\attrs.c" "$(WorkDir)Tidy-Html5\src\buffio.c" "$(WorkDir)Tidy-Html5\src\charsets.c" "$(WorkDir)Tidy-Html5\src\clean.c" "$(WorkDir)Tidy-Html5\src\config.c" "$(WorkDir)Tidy-Html5\src\entities.c" "$(WorkDir)Tidy-Html5\src\fileio.c" "$(WorkDir)Tidy-Html5\src\gdoc.c" "$(WorkDir)Tidy-Html5\src\iconvtc.c" "$(WorkDir)Tidy-Html5\src\istack.c" "$(WorkDir)Tidy-Html5\src\lexer.c" "$(WorkDir)Tidy-Html5\src\localize.c" "$(WorkDir)Tidy-Html5\src\mappedio.c" "$(WorkDir)Tidy-Html5\src\parser.c" "$(WorkDir)Tidy-Html5\src\pprint.c" "$(WorkDir)Tidy-Html5\src\sprtf.c" "$(WorkDir)Tidy-Html5\src\streamio.c" "$(WorkDir)Tidy-Html5\src\tagask.c" "$(WorkDir)Tidy-Html5\src\tags.c" "$(WorkDir)Tidy-Html5\src\tidylib.c" "$(WorkDir)Tidy-Html5\src\tmbstr.c" "$(WorkDir)Tidy-Html5\src\utf8.c" "$(WorkDir)Tidy-Html5\src\win32tc.c" "$(WorkDir)Tidy.c" 

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
