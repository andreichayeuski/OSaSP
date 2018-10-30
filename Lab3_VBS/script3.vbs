
Set WshShell = CreateObject ("WScript.Shell")
Set objEnv = WshShell.Environment("User")
objEnv("MyVar") = "xcopy file1.txt file2.txt"
WshShell.Run objEnv("MyVar")