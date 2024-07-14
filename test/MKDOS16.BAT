@ECHO OFF

wcl TEST.C -fe=TEST16.EXE
if errorlevel 1 goto :end

wcl WCTEST.C -fe=WCTEST16.EXE
if errorlevel 1 goto :end

echo done

:end
