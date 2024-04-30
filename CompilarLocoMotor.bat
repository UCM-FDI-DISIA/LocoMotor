call .\CompilarDependencias.bat

msbuild LocoMotor.sln /p:configuration=Debug  
msbuild LocoMotor.sln /p:configuration=Release 
