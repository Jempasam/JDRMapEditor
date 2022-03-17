@echo off

set /p size=Taille de la carte:
set x=0
set y=0

for /l %%x in (0, 1, %size%) do (

for /l %%y in (0, 1, %size%) do (

copy "basetile.trrn" "result/%%x%%y.trrn"
copy "baseentity.trrn" "result/EntitiesMap/%%x%%y.trrn"

)

)

pause