
set BASE=c:\mingw_5.3.0\
set PATH=%BASE%bin;%PATH% 
set C_INCLUDE_PATH=%BASE%include;%BASE%i686-pc-mingw32\include;%BASE%include;%BASE%include\glib
set CPLUS_INCLUDE_PATH=%BASE%include\g++
set LIBRARY_PATH = %BASE%lib;%BASE%i686-pc-mingw32\lib;%BASE%lib
set GCC_EXEC_PREFIX = %BASE%lib\gcc-lib\
set GDKLIB= -fnative-struct -mwindows -lgtk-1.3 -lgdk-1.3 
set GCC_OPT_SJIS=-finput-charset=cp932 -fexec-charset=cp932

cd C:\gcc_pjt
explorer "C:\gcc_pjt"
cmd
