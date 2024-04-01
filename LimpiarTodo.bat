cd bin
del /s *.dll
del /s *.pdb
del /s *.exe
cd ..\Dependencies\Ogre\
rmdir build /s
cd ..\Bullet\
rmdir build /s
cd ..
cd ..
