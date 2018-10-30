echo off
cls
set n=0 1 2 3 4 5 6 7 8 9 A B C D E F
set f=7
for %%x in (%n%) do (
for %%y in (%f%) do (
color %%x%%y
timeout 1 >nul
)
)
