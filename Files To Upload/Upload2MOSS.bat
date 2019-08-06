@ECHO off
setlocal
:PROMPT
ECHO **********************************************************
ECHO This .bat file will upload ALL files in target local 
ECHO directory to target directory on MOSS.
ECHO Any files with spaces will not upload.
ECHO **********************************************************
SET /P AREYOUSURE=Are you sure you wish to continue (Y/[N])?
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END
FOR /F %%G IN ('DIR /b "%cd%"') DO pscp -pw "C03we399innvriyuesad" "%%G" "s4530941@moss.labs.eait.uq.edu.au:Documents/ass1"
:END
endlocal
PAUSE