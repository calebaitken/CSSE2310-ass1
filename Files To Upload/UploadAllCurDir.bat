@ECHO off
setlocal
:PROMPT
ECHO **********************************************************
ECHO Any files with spaces will not upload due to the linux OS
ECHO This BAT will upload to Documents/ass1
ECHO **********************************************************
SET /P AREYOUSURE=Are you sure you wish to continue (Y/[N])?
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END
SET /P PWD=Please enter the MOSS password:
FOR /F %%G IN ('DIR /b "%cd%"') DO pscp -pw "%PWD%" "%%G" s4530941@moss.labs.eait.uq.edu.au:Documents/ass1
:END
endlocal
PAUSE