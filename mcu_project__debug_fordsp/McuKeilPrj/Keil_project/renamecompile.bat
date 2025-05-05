@echo off
setlocal enabledelayedexpansion

rem 获取当前日期和时间，替换非法字符 
set TARGET_NAME=Project_app
set datetime=%DATE:~0,4%%DATE:~5,2%%DATE:~8,2%_%TIME:~0,2%%TIME:~3,2%
set datetime=%datetime: =0%
set datetime=%datetime::=%

rem 定义原始文件和新文件名
set "source=.\Output\%TARGET_NAME%.bin"
set "dest=.\Output\%TARGET_NAME%_%datetime%.bin"

rem 复制文件并重命名
copy "%source%" "%dest%" 

rem 复制axf
set "source_axf=.\Output\%TARGET_NAME%.axf"
set "dest_axf=.\Output\%TARGET_NAME%_%datetime%.axf"  
copy "%source_axf%" "%dest_axf%"
  

echo renmae file: %dest%
endlocal
