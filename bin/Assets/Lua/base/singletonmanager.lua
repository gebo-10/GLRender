require("systool.baseclass")

-- SingletonManager
-- 所有单例的管理类，会统一调用以下几个接口：
-- Update()
-- ResetData()
-- Destroy()

SingletonManager = SingletonManager or BaseClass()

function SingletonManager:__init()
    self.singleton_list = {}
end

function SingletonManager:__delete()
    self.singleton_list = nil
end

function SingletonManager:RegisterSingleton(class_name, instance)
    if self.singleton_list[class_name] then
        error("double register singleton, class name is " .. class_name)
    end
    self.singleton_list[class_name] = instance
end

function SingletonManager:RemoveSingleton(class_name)
    self.singleton_list[class_name] = nil
end

function SingletonManager:Update(delta_time)
    for k, v in pairs(self.singleton_list) do
        StatHelperInstance:BeginSample("GlobalSingletonManager" .. k)
        v:Update(delta_time)
        StatHelperInstance:EndSample()
    end
end

function SingletonManager:ResetData()
    for k, v in pairs(self.singleton_list) do
        v:ResetData()
    end
end

function SingletonManager:Destroy()
    for k, v in pairs(self.singleton_list) do
        v:Destroy()
    end
    --self.singleton_list = {}
end

