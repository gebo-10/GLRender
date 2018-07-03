--利用ID分离对EventSystem的直接引用
_inner_event_system_list = _inner_event_system_list or {}
_inner_event_system_id_count = _inner_event_system_id_count or 0

EventSystem = EventSystem or BaseClass()
--事件系统(非单健)
function EventSystem:__init()
	_inner_event_system_id_count = _inner_event_system_id_count + 1
	self.system_id = _inner_event_system_id_count
	_inner_event_system_list[self.system_id] = self

	--需要激发的事件(延后调用方式)
	self.need_fire_events = List.New()

	--事件列表
	self.event_list = {}

	self.delay_handle_list = {}

	self.delay_id_count = 0

	self.is_deleted = false
	
	--self.timer_quest_manager = TimerQuest()
	
	self.obj_bind = {}
end

--调用已经处于派发队列中的Event
function EventSystem:Update()
	--timer quest
	--self.timer_quest_manager:Update(Status.NowTime, Status.ElapseTime)
	local tempList = self.need_fire_events
	self.need_fire_events = List.New()

	--依次执行所有需要触发的事件
	while not List.Empty(tempList) do
		local fire_info = List.PopFront(tempList)
		fire_info.event:Fire(fire_info.arg_list)
	end
end

function EventSystem:Bind(event_id, event_func, obj_key)
	if event_id == nil then
		error("Try to bind to a nil event_id")
		return
	end
	if obj_key == nil then
		print("event_id", event_id)
		error("obj_key cannot be nil. May use 'self' as third argument when calling EventSystem:Bind")
		return
	end

	if self.is_deleted then
		return
	end

	-- 检查是否重复绑定  by huanjiang
	local has = nil
	if self.obj_bind[obj_key] ~= nil then
		has = self.obj_bind[obj_key][event_id]
	else
		self.obj_bind[obj_key] = {}
	end
	if has then
		error("object has already registered to the event: "..event_id)
	else
		self.obj_bind[obj_key][event_id] = 1
	end
	
	if self.event_list[event_id] == nil then
		self:CreateEvent(event_id)
	end
	local tmp_event = self.event_list[event_id]
	
	return tmp_event:Bind(event_func)
end

function EventSystem:UnBind(event_handle, obj_key)
	if event_handle == nil then
		return
	end
	if event_handle.event_id == nil then
		error("Try to unbind a nil event_id")
		return
	end
	if obj_key == nil then
		print("event_handle", event_handle)
		error("obj_key cannot be nil. May use 'self' as third argument when calling EventSystem:Unbind")
		return
	end
	if self.obj_bind[obj_key] ~= nil and self.obj_bind[obj_key][event_handle.event_id] then
			self.obj_bind[obj_key][event_handle.event_id] = nil
			local sub_count = 0
			for index,v in pairs(self.obj_bind[obj_key]) do
				sub_count = sub_count + 1
			end
			if sub_count <= 0 then			
				self.obj_bind[obj_key] = nil
			end
	else
		--error("object has NOT been registerd to the event: "..event_id)
		return
	end

	if self.is_deleted then
		return
	end

	local tmp_event = self.event_list[event_handle.event_id]
	if tmp_event ~= nil then
		tmp_event:UnBind(event_handle)
	end
end

--立即触发
function EventSystem:Fire(event_id, ...)
	if event_id == nil then
		error("Try to call EventSystem:Fire() with a nil event_id")
		return
	end


	if self.is_deleted then
		return
	end
	
	local tmp_event = self.event_list[event_id] 
	if tmp_event ~= nil then
		tmp_event:Fire({...})
	end
end

--下一帧触发
function EventSystem:FireNextFrame(event_id, ...)
	if event_id == nil then
		error("Try to call EventSystem:FireNextFrame() with a nil event_id")
		return
	end


	if self.is_deleted then
		return
	end

	local tmp_event = self.event_list[event_id] 
	if tmp_event ~= nil then
		local fire_info = {}
		fire_info.event = tmp_event
		fire_info.arg_list = {...}
		List.PushBack(self.need_fire_events, fire_info)
	end
end

function EventSystem:FireDelay(event_id, delay_time, ...)
	--[[
	if event_id == nil then
		error("Try to call EventSystem:FireDelay() with a nil event_id")
		return
	end

	if self.is_deleted then
		return
	end

	self.delay_id_count = self.delay_id_count + 1
	local delay_id = self.delay_id_count
	local system_id = self.system_id
	local arg_list = {...}
	local delay_call_func = function()
		--print("delay func")
		local obj = _inner_event_system_list[system_id]
		if obj~= nil then
			obj:Fire(event_id, unpack(arg_list))	--执行定时任务
			obj.delay_handle_list[delay_id] = nil	--删除该句柄
		end
	end
	local quest_handle = self.timer_quest_manager:AddDelayQuest(delay_call_func, delay_time)
	self.delay_handle_list[delay_id] = quest_handle
	]]
end

function EventSystem:CreateEvent(event_id)
	self.event_list[event_id] = Event.New(event_id)
end

function EventSystem:__delete()
	if not self.is_deleted then
		--self.timer_quest_manager:Stop()
		self.timer_quest_manager = nil	

		_inner_event_system_list[self.system_id] = nil
		self.is_deleted = true
	end
end


