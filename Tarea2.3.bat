@echo off
set/p "time=Enter time value..."
echo %time%
shutdown /s /t %time%
echo la computadora se va a apagar en %time% segundos
timeout 10
shutdown /a
echo el timer se cancelo
pause
