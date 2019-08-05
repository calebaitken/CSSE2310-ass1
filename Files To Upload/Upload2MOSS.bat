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
SET /P LDIR=Please enter target LOCAL directory (use %%cd%% for current directory):
SET /P RDIR=Please enter target MOSS directory (leave blank for home directory):
SET /P USR=Please enter your MOSS username:
SET /P PWD=Please enter the MOSS password:
FOR /F %%G IN ('DIR /b "%cd%"') DO pscp -pw "%PWD%" "%%G" "%USR%@moss.labs.eait.uq.edu.au:%RDIR%"
:END
endlocal
PAUSE