Option Explicit
Dim FSO, Batch, path, WshShell, WshShell2
Set FSO = CreateObject("Scripting.FileSystemObject")
Set Batch = FSO.OpenTextFile("D:\Документы\Университет\5 семестр\ОСиСП\Отчёты\lab3\colorandmusic.bat", 2, True)
Batch.WriteLine "echo off"
Batch.WriteLine "cls"
Batch.WriteLine "set n=0 1 2 3 4 5 6 7 8 9 A B C D E F"
Batch.WriteLine "set f=7"
Batch.WriteLine "for %%x in (%n%) do ("
Batch.WriteLine "for %%y in (%f%) do ("
Batch.WriteLine "color %%x%%y"
Batch.WriteLine "timeout 1 >nul"
Batch.WriteLine ")"
Batch.WriteLine ")"
Batch.Close
Set WshShell = CreateObject("WScript.Shell")
WshShell.Run "C:\Users\andre\Downloads\prokofiev.mp3"
Set WshShell2 = CreateObject("WScript.Shell")
WshShell2.Run "colorandmusic.bat", 1, True

