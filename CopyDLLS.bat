:: OGRE
set BIN=.\bin\
set OgreBuild=.\Dependencies\Ogre\build
set LuaBuild=.\Dependencies\Lua\build
set FmodDir=.\Dependencies\FMOD

mkdir %BIN%

COPY /y %OgreBuild%\bin\debug\Codec_STBI_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\OgreMain_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\RenderSystem_Direct3D11_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\zlib.dll %BIN%
COPY /y %OgreBuild%\bin\debug\OgreRTShaderSystem_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\Plugin_ParticleFX_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\OgreOverlay_d.dll %BIN%

COPY /y %OgreBuild%\bin\release\Codec_STBI.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreMain.dll %BIN%
COPY /y %OgreBuild%\bin\release\RenderSystem_Direct3D11.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreXMLConverter.exe %BIN%
COPY /y %OgreBuild%\bin\release\OgreMeshUpgrader.exe %BIN%
COPY /y %OgreBuild%\bin\release\SDL2.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreRTShaderSystem.dll %BIN%
COPY /y %OgreBuild%\bin\release\Plugin_ParticleFX.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreOverlay.dll %BIN%

COPY /y %FmodDir%\core\lib\fmod.dll %BIN%
COPY /y %FmodDir%\core\lib\fmodL.dll %BIN%

COPY /y %LuaBuild%\Lua.dll %BIN%
COPY /y %LuaBuild%\Lua_d.dll %BIN%
