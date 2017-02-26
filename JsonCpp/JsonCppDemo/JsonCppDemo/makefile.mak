#��������ʾ��α���MFC����
##########################��������ʽ��makefile���##########################
#�����������ɵĿ�ִ���ļ����� 
ProjName=JsonCppDemo.exe

#���ɶ������ļ�֮�������ʱ�ļ�
All:$(ProjName) clean

#�����Ҫ����LIB�ĵط� 
NormalLIB=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

#ͨ�õ����ӵ�������Ϣ 
LinkProj=/nologo /subsystem:console /incremental:no

#����Ŀ���ļ�
$(ProjName):cppCompileStep
    @echo ����Ŀ���ļ�
    Link.exe Demo.obj json_value.obj json_reader.obj json_writer.obj $(NormalLIB) $(LinkProj) /OUT:$(ProjName)

#��������ΪUNICODE��MBCS
StrType=UNICODE

#ͨ�õı���Դ�ļ���������Ϣ��ע�⣬��VC6.0�У���û��֧��/Zc:wchar_tŶ
CLProj=/MT /EHsc /c /W4 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_$(StrType)" /D "$(StrType)"

#����Դ�ļ�
cppCompileStep:
    @echo ����Դ�ļ�
    cl.exe $(CLProj) Demo.cpp JsonCpp\json_value.cpp JsonCpp\json_reader.cpp JsonCpp\json_writer.cpp

#����м��ļ�
clean:
    @echo ����м��ļ�
    @del *.obj *.idb *.pdb
    @echo ִ����ɣ�������\(^_^)(^_^)/

##########################��������ʽ��makefile���##########################
    