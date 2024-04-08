Prueba = {}
Prueba.__index = Polla
function Prueba:new()
	local obj={}
	setmetatable(obj, Prueba)
	return obj
end
Polla:helloWorld()
prueba1 = Prueba:new()
prueba1:helloWorld()