set BLENDERPATH=C:\Program Files/Blender Foundation/Blender 3.6
C:
cd %BLENDERPATH%\3.6\python\bin
python -m ensurepip
python -m pip install scipy
set PATH=%PATH%;%BLENDERPATH%
D:
cd D:\Projects\physics\render
blender -b -P test.py