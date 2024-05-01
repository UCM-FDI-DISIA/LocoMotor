cd bin
del /s *.dll
del /s *.exe

echo Deleting Ogre build...
cd ..\Dependencies\Ogre\
rmdir /s /q build

echo Deleting Bullet build...
cd ..\Bullet\
rmdir /s /q build

cd ..
cd ..
