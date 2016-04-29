echo off
set /p CFile= "Enter the file name to execute?  "
setx CFile "%CFile%"
echo %CFile%
echo Starting conversion of .fl file to Intermediate code .fl .cls
"%cd%\Compiler\flash.exe" "%cd%\FlashCode\%CFile%"
echo Intermediate Code Generated in Runtime folder with a .fl.cls extension
echo Press a key to Execute Intermediate Code ans see the result
PAUSE
java -classpath "%cd%"\bin\ FlashExecutor "%cd%\FlashCode\%CFile%.cls"
echo 
echo Intermediate Code will be deleted if you continue. If you want to save it copy the file to a different location.
PAUSE
del "%cd%\FlashCode\%CFile%.cls"