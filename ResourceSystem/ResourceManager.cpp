#include <ResourceManager.h>
ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::Init(string root)
{
	res_root = root;
	return file.Init();

}

void ResourceManager::Update(Uint32 delta)
{
	file.Update(delta);
}

bool ResourceManager::Cache(string filename, ResPtr res)
{
	return true;
}

bool ResourceManager::DeCache(string filename)
{
	return true;
}

bool ResourceManager::GetRes(string name, std::function<void(ResPtr) > cb)
{
	auto itr = cache.find(name);
	if (itr!= cache.end() && !itr->second.expired() )
	{
		ResPtr ptr = itr->second.lock();
		cb(ptr);
	}
	else
	{
		file.OpenFile(res_root + name, [=](FileWork * work) {
			ResItem * item = new ResItem;
			item->buff = work->buff;
			item->size = work->size;
			item->filename = name;

			ResPtr ptr(item, [=](ResItem * res) {
				cout << "Res decache:" << res->filename << endl;
				this->DeCache(res->filename);
				delete res;
			});//make_shared 不支持删除器 无法优化内存分配
			
			cb(ptr);
			this->cache.insert({ name, ptr });
		});
	}

	return true;
}

bool ResourceManager::GetBigRes(string name, std::function<void(ResPtr) > cb)
{
	return true;
}

bool ResourceManager::SaveRes(string name, ResPtr res)
{
	return true;
}

