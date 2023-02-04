@echo off
cd C:\
mkdir Ejercicio
dir 
move "C:\Ejercicio" "C:\Users\alex_\OneDrive\Escritorio"
dir
cd C:\Users\alex_\OneDrive\Escritorio
dir
rd C:\Users\alex_\OneDrive\Escritorio\Ejercicio
dir
echo termino la ejecucion
pause
exit
