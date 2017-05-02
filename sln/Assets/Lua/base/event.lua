--用于唯一标识obj的table
require("systool.baseclass")

_inner_event_connection_obj = _inner_event_connection_obj or {}

Event = Event or BaseClass()

function Event:__init(event_id)
	self.event_id = event_id
	self.bind_id_count = 0
	self.event_func_list = {}
end

function Event:Fire(arg_table)
	for _, func in pairs(self.event_func_list) do
		func(unpack(arg_table))
	end
end

function Event:UnBind(obj)
	--仅当obj符合类型时才作对应操作
	if getmetatable(obj) == _inner_event_connection_obj and obj.event_id == self.event_id then
		self.event_func_list[obj.bind_id] = nil
	end
end

function Event:Bind(event_func)
	self.bind_id_count = self.bind_id_count + 1
	local obj = {}
	setmetatable(obj, _inner_event_connection_obj)
	obj.event_id = self.event_id
	obj.bind_id = self.bind_id_count
	self.event_func_list[obj.bind_id] = event_func
	return obj
end

