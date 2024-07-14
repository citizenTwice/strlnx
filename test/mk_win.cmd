@ECHO OFF

cl TEST.C /Fe:WIN_TEST.EXE
if errorlevel 1 goto :end

cl WCTEST.C /Fe:WIN_WCTEST.EXE
if errorlevel 1 goto :end

echo done

:end 
