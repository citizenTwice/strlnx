@ECHO OFF

wcl386 TEST.C -fe=TEST.EXE
if errorlevel 1 goto :end

wcl386 WCTEST.C -fe=WCTEST.EXE
if errorlevel 1 goto :end

echo done

:end
