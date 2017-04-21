#在这里演示如何编译MFC工程
##########################下面是正式的makefile语句##########################
#设置最终生成的可执行文件名称 
ProjName=regexcdemo.exe

#生成二进制文件之后清除临时文件
All:$(ProjName) clean

#填充需要连接LIB的地方 
NormalLIB=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

#通用的链接的配置信息 
LinkProj=/nologo /subsystem:console /incremental:no

#连接目标文件
$(ProjName):cppCompileStep
    @echo 链接目标文件
    Link.exe main.obj regex.obj $(NormalLIB) $(LinkProj) /OUT:$(ProjName)

#可以设置为UNICODE或MBCS
#StrType=MBCS
StrType=UNICODE

#通用的编译源文件的设置信息，注意，在VC6.0中，还没有支持/Zc:wchar_t哦
CLProj=/MD /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_$(StrType)" /D "$(StrType)"

#编译源文件
cppCompileStep:
    @echo 编译源文件
    cl.exe $(CLProj) main.c
    cl.exe $(CLProj) regex.c
    
#清空中间文件
clean:
    @echo 清空中间文件
    @del *.obj *.idb *.pdb
    @echo 执行完成，请验收\(^_^)(^_^)/

##########################上面是正式的makefile语句##########################
    