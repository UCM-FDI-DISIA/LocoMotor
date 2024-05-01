set LuaBuild=.\build

mkdir %LuaBuild%

msbuild Lua.sln /p:configuration=Debug
msbuild Lua.sln /p:configuration=Release