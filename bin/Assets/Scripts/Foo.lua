Foo = {behaviour = behaviour}
Foo.__index = Foo
print(Prueba)
print(Foo)
function Foo:start()
    print("self ")print(self)
    print("Prueba ")print(self.behaviour:gameObject():getBehaviour("Prueba"):getScript())
    print("Foo ")print(self.behaviour:gameObject():getBehaviour("Foo"):getScript())
    self.behaviour:gameObject():getBehaviour("Prueba"):getScript():si()
    
    self.behaviour:gameObject():getBehaviour("Foo"):getScript():p()
    
    print(self.behaviour:gameObject():getTr():getPosition().x)
    
end

function Foo:p()
    print("print")
end

