Prueba = {}
Prueba.__index = Prueba

function Prueba:new()
    local obj = {}
    setmetatable(obj, Prueba)
    return obj
end

function Prueba:update(dt)
    print("Hola Buenas desde el update")
end

function Prueba:start()
    print("Hola Buenas desde el update")
end

PruebaVar = Prueba:new()