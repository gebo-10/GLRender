--保存类类型的虚表
local _class = {}

GLOBAL_OBJ_COUNT = {}

OPEN_PROFILER_SAMPLE = false

if OPEN_PROFILER_SAMPLE then
	ENABLE_OBJ_COUNT = 1
else
	ENABLE_OBJ_COUNT = 0
end

function FindClassName(target, depth)
	for key,value in pairs(_G) do
		if value == target then
			return key
		end
	end
end

function ClasCountRetain(c)
	local key = FindClassName(c)
	if GLOBAL_OBJ_COUNT[key] == nil then
		GLOBAL_OBJ_COUNT[key] = 1
	else
		GLOBAL_OBJ_COUNT[key] = GLOBAL_OBJ_COUNT[key] + 1
	end
end

function ClasCountRelease(c)
	local key = FindClassName(c)
	if GLOBAL_OBJ_COUNT[key] == nil then
		GLOBAL_OBJ_COUNT[key] = -100000--标识异常
	else
		GLOBAL_OBJ_COUNT[key] = GLOBAL_OBJ_COUNT[key] - 1
	end
end




function PrintLuaClassCount( ... )
	loginfo("PrintLuaClassCount_begin............")
	for key,value in pairs(GLOBAL_OBJ_COUNT) do
		loginfo("LuaClassCount:"..key..":",value)
	end

	loginfo("PrintLuaClassCount_end............")
end

local UI_DIC = {
	["UIWidget"] = true,
	["UIScrollViewContent"] =  true,
	["UIButton"] = true,
	["UIRichlabel"] = true,
	["UILabel"] = true,
	["UISprite"] = true,
	["UIWidgetContainer"] = true,
	["UIInput"] = true,
	["UIPanel"] = true,
	["UITexture"] = true,
	["UISlider"] = true,
	["UIExFrameASprite"] = true,
	["UIToggle"] = true,
	["UnityEngine.GameObject"] = true,
	["UnityEngine.Transform"] = true,
	["ExUIButton"] = true,

}


local function CheckIsUIComponent(v)
	if not v then
		return false
	end

	if  v.GetClassType then
		local component_type = v:GetClassType()
		-- loginfo("component_type ", component_type, tostring(component_type), tbl.layout_name )
		if UI_DIC[tostring(component_type)] then
			return true
		end
	end

	return false
end


function BaseClass(super)

	-- 生成一个类类型
	local class_type = {}
	-- 在创建对象的时候自动调用
	class_type.__init = false
	class_type.__delete = false
	class_type.super = super

	class_type.New = function(...)
		-- 生成一个类对象
		local obj = {}
		
		local index_function
		local newindex_function
		if super and super.BASE_UI_TAG then
			local obj_data = {}
			setmetatable(obj_data, { __index = _class[class_type]})
			index_function = function (tbl, k)
				return obj_data[k]
			end
			newindex_function = function (tbl, k, v)
				obj_data[k] = v
			end
		else
			index_function = _class[class_type]
			newindex_function = function (tbl, k, v)
				rawset( tbl, k, v )
			end
		end

		obj._class_type = class_type

		-- 在初始化之前注册基类方法
		setmetatable(obj, { __index = index_function ,  

				__newindex = function (tbl, k, v)
					if _class[class_type].BASE_UI_TAG  then
						if not tbl["ui_tag"] then
							rawset(tbl,"ui_tag", {})
						end 
						if v ~= nil then
							local v_type = type(v)
							if (v_type == "userdata"  and CheckIsUIComponent(v)) or (type(k) == "userdata" and CheckIsUIComponent(k)) then
								tbl.ui_tag[ #tbl.ui_tag  + 1 ] = k
							elseif v_type == "table" and  not next(v)  then
								
								setmetatable(v, { 
									__newindex = function (tbl2, k2, v2)
										local v2_type = type(v2)
										if (v2_type == "userdata" and CheckIsUIComponent(v2)) or (type(k2) == "userdata" and CheckIsUIComponent(k2)) then
											if not tbl.ui_tag[k] then tbl.ui_tag[k] = {} end
											table.insert(tbl.ui_tag[k], k2)
										elseif v2_type == "table" and  not next(v2)  then
											
											setmetatable( v2, {
												__newindex = function (tbl3, k3, v3)
													local v3_type = type(v3)
													if (v3_type == "userdata" and CheckIsUIComponent(v3)) or (type(k3) == "userdata" and CheckIsUIComponent(k3)) then
														if not tbl.ui_tag[k] then tbl.ui_tag[k] = {} end
														if not tbl.ui_tag[k][k2] then tbl.ui_tag[k][k2] = {} end
														table.insert(tbl.ui_tag[k][k2], k3)
														-- tbl.ui_tag[ #tbl.ui_tag +1 ] = k ..Insert(k2) .. k2..Insert(k3) .. k3
 													end
 													rawset(tbl3, k3, v3)
												end
												} )

										end
										rawset( tbl2, k2, v2 )
									end  } 
								) 

							end
						end
					end
					newindex_function(tbl, k, v)
				end 
		}
			)

		-- 调用初始化方法
		do
			local create 
			create = function(c, ...)
				if c.super then
					create(c.super, ...)
				end
				if ENABLE_OBJ_COUNT ~= 0 then
					ClasCountRetain(c)
				end
				if c.__init then
					c.__init(obj, ...)
				end
			end

			create(class_type, ...)
		end

		-- 注册一个delete方法
		obj.DeleteMe = function(self)
			local now_super = self._class_type 
			while now_super ~= nil do
				if ENABLE_OBJ_COUNT ~= 0 then
					ClasCountRelease(now_super)
				end	
				if now_super.__delete then
					now_super.__delete(self)
				end
				now_super = now_super.super
			end
		end

		return obj
	end

	local vtbl = {}
	_class[class_type] = vtbl	

	setmetatable(class_type, {__newindex =
		function(t,k,v)
			vtbl[k] = v
		end
		, 
		__index = vtbl, --For call parent method
	})

	if super then
		setmetatable(vtbl, {__index =
			function(t,k)
				local ret = _class[super][k]
				--do not do accept, make hot update work right!
				--vtbl[k] = ret
				return ret
			end
		})
	end

	return class_type
end