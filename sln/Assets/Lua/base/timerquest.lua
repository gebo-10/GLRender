TimerQuest = TimerQuest or BaseClass()

---------------------------------------------------------------------------------------------------
TimerQuestItem = TimerQuestItem or BaseClass()

function TimerQuestItem:__init(id, agent, quest_func)
	self.id = id
	self.agent = agent
	self.quest_func = quest_func
	self.run_cnt = 0
	self.next_run_time = -1
	self.run_period = 0
	self.is_always_run = false
	self.lost_time = -1
	self.period_growth = math.huge
end

function TimerQuestItem:__delete()
	self.quest_func = nil
	self.agent = nil
end

function TimerQuestItem:Run()
	if not self.agent:IsQuestAlive( self.id ) then
		return true
	end
	
	if self.quest_func then
		self.quest_func()
	end
	-- local need_del = pcall( self.quest_func )
	-- if need_del ~= true then 
	-- 	print("qeust_id  ".. self.id .." quest_func has error !!" , self.quest_func )
	-- 	return true 
	-- end
	self.run_cnt = self.run_cnt +1

	if self.period_growth ~= math.huge then
		self.run_period = self.run_period + self.period_growth
	end

	self.next_run_time = self.next_run_time + self.run_period

	if (not self.is_always_run) and ( self.next_run_time > self.lost_time ) then
		return true
	end
	return false
end


---------------------------------------------------------------------------------------------------------


function TimerQuest:Instance()
	if not TimerQuest.instance then
		TimerQuest.New()
	end
	return TimerQuest.instance
end

function TimerQuest:__init()
	if TimerQuest.instance then 
		error( "TimerQuest instance is existed" )
	end

	TimerQuest.instance = self
	self.id_cnt = 0 
	self.now_time = 0
	self.timer_quest_map = {}
	self.keep_id_set = {}
end

function TimerQuest:DeleteMe()
	self.timer_quest_map = nil
	TimerQuest.instance = nil
end


--[[延时执行一个任务]]
function TimerQuest:AddDelayQuest(quest_func, delay_time)
	self.id_cnt = self.id_cnt + 1
	local quest = TimerQuestItem.New(self.id_cnt, self,  quest_func)

	quest.is_always_run = false	
	quest.next_run_time = self.now_time + delay_time 

	if not self.timer_quest_map[quest.next_run_time] then
		self.timer_quest_map[quest.next_run_time] = {}
	end

	table.insert(self.timer_quest_map[quest.next_run_time], quest )
	self.keep_id_set[quest.id] = true
	return quest.id
end

--[[周期性执行一个任务]]
function TimerQuest:AddPeriodQuest(quest_func, period, last_time)
	self.id_cnt = self.id_cnt + 1
	local quest = TimerQuestItem.New( self.id_cnt, self, quest_func )
	quest.is_always_run = (last_time < 0.0)					
	quest.next_run_time = self.now_time + period			
	quest.run_period = period								
	quest.lost_time = self.now_time + last_time				

	if not self.timer_quest_map[quest.next_run_time] then
		self.timer_quest_map[quest.next_run_time] = {}
	end
	table.insert(self.timer_quest_map[quest.next_run_time], quest )
	self.keep_id_set[quest.id] = true
	return quest.id
end


--[[周期性执行任务指定次数]]
function TimerQuest:AddRunTimesQuest( quest_func, period, run_count)
	self.id_cnt = self.id_cnt + 1
	local quest = TimerQuestItem.New( self.id_cnt, self, quest_func )
	
	quest.is_always_run = (run_count < 0)								
	quest.next_run_time = self.now_time + period						
	quest.run_period = period											
	quest.lost_time = self.now_time + period*run_count + 0.1*period 	

	if not self.timer_quest_map[quest.next_run_time] then
		self.timer_quest_map[quest.next_run_time] = {}
	end
	table.insert(self.timer_quest_map[quest.next_run_time], quest )
	self.keep_id_set[quest.id] = true

	return quest.id
end

--[[周期性任务 周期起点 周期增量 持续时间 ]]
-- !!! 周期为负数将导致任务一直执行
function TimerQuest:AddPeriodGrowthQuest( quest_func, period_start, period_growth, last_time )
	self.id_cnt =  self.id_cnt + 1
	local quest = TimerQuestItem.New( self.id_cnt, self, quest_func )

	quest.is_always_run = (last_time < 0.0)	
 	quest.next_run_time =  self.now_time + period_start    
	quest.run_period = period_start
	quest.lost_time = self.now_time + last_time
	quest.period_growth = period_growth

	if not self.timer_quest_map[ quest.next_run_time ] then
		self.timer_quest_map[quest.next_run_time] = {}
	end
	table.insert( self.timer_quest_map[quest.next_run_time], quest)
	self.keep_id_set[quest.id] = true

	return quest.id
end

function  TimerQuest:CancelQuest( quest_id )
	if quest_id == nil then 
		return 
	end
	self.keep_id_set[quest_id] = nil
end


function TimerQuest:Stop()
	self.timer_quest_map = {}
	self.keep_id_set = {}
end

function TimerQuest:IsQuestAlive( quest_id )
	if self.keep_id_set[quest_id] then
		return true
	end
	return false
end

function TimerQuest:GetExecutableQuest(now_time)
	local questKeyMap = {}
	for key, value in pairs(self.timer_quest_map) do
		if key <= now_time then
			table.insert(questKeyMap, key)
		end
	end
	return questKeyMap 
end

function  TimerQuest:Update(now_time, elapse_time)
	self.now_time = now_time
	local questKeyMap = self:GetExecutableQuest(now_time)

	for _, value in ipairs(questKeyMap) do
		local questSet = self.timer_quest_map[value]

		for index, quest in ipairs(questSet) do
			local need_del = quest:Run()
			if not need_del then
				if not self.timer_quest_map[quest.next_run_time] then
					self.timer_quest_map[quest.next_run_time] = {}
				end
				table.insert( self.timer_quest_map[quest.next_run_time], quest)
			else
				self:CancelQuest( quest.id )
				quest:DeleteMe()
				quest = nil
			end
		end

		self.timer_quest_map[value] = nil
	end
end