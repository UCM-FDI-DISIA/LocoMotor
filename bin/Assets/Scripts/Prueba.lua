Prueba = {}
Prueba.__index = Prueba

function Prueba:new()
    local obj = {}
    setmetatable(obj, Prueba)
    return obj
end

function Prueba:update(dt)
    ---print(dt)
    ---print("Hola Buenas desde el update")
end

function Prueba:start()
    ---print("Hola Buenas desde el update")
end

function Prueba:setParameters(params) 
    print("SetParameters")
    for n,p in pairs(params) do
        print(n)
        print(p)
    end 
    print(params["parametro"])
end

PruebaVar = Prueba:new()