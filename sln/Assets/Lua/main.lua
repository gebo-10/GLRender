package.path=GameConfig.lua_path
require("test")
print("Script Lua Loaded...")
test()
s=Student()
s:Run2(121)
function Start()
	print("Script Start")
end
function Update()
	--print("Script Update")
end
function Stop()
	print("Script Stop")
end
