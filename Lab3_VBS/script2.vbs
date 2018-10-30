
Set WshShell = CreateObject ("WScript.Shell")
Set objEnv = WshShell.Environment("User")
objEnv("MyVar") = "notepad.exe path"
WshShell.Run objEnv("MyVar")