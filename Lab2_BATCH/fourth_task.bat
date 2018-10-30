systeminfo | find "BIOS" > info.txt
systeminfo | find "Версия ОС" >> info.txt
type info.txt
