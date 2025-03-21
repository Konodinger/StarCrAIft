start cmd /c "PMRBot_d.exe"
cd ../starcraft
start cmd /c RunStarcraftWithBWAPI.bat

TIMEOUT /T 2
for /f "TOKENS=1,2,*" %%a in ('tasklist /FI "ImageName eq PMRBot_d.exe"') do set MyPID=%%b
//vsjitdebugger -p %MyPID%