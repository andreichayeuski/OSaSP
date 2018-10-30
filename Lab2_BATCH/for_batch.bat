 REM вывести на экран количество файлов каждого расширения
 set /a txt_file = "0"
 set /a exe_file = "0"
 set /a bat_file = "0"
 FOR %%f IN (dir %1\*.txt) DO Set /a txt_file += "1" 
 FOR %%a IN (dir %1\*.bat) DO Set /a bat_file += "1" 
 FOR %%b IN (dir %1\*.exe) DO Set /a exe_file += "1"
 Set /a txt_file -= "1" 
 Set /a bat_file -= "1" 
 Set /a exe_file -= "1" 
echo %txt_file%
echo %bat_file%
echo %exe_file%