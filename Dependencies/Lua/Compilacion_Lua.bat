set LuaBuild=.\build

rmdir /s /q %LuaBuild%

mkdir %LuaBuild%

msbuild Lua.sln /p:configuration=Debug
msbuild Lua.sln /p:configuration=Release