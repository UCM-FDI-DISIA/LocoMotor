
Prueba = {behaviour = behaviour, name = "Pene"}
Prueba.__index = Prueba
print(Prueba)
print(Foo)
function Prueba:new()
    local obj = {}
    setmetatable(obj,Prueba)
    return obj
end

function Prueba:awake()
    print("Prueba awake")
end
function Prueba:update(dt)
    ---print(dt)
    ---print("Hola Buenas desde el update")
   
    
end

function Prueba:start()
    ---self:foo()
   
end

function Prueba:setParameters(params) 
    print("SetParameters")
    for n,p in pairs(params) do
        print(n)
        print(p)
    end 
    print(params["parametro"])
end

function Prueba:si()
    print("Funcion desde lua")
    print(self.name)
end
