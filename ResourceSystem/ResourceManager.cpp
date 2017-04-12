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

bool ResourceManager::GetRes(string name, std::function<void(ResItem*) > cb)
{
	auto itr = cache.find(name);
	if (itr!= cache.end())
	{
		cb(itr->second);
	}
	else
	{
		file.OpenFile(res_root + name, [=](FileWork * work) {
			ResItem * item = new ResItem;
			item->buff = work->buff;
			item->size = work->size;
			//cout.write((char *)work->buff, work->size);
			cb(item);
			this->cache.insert({ name, item });
		});
	}

	return true;
}

bool ResourceManager::GetBigRes(string name, std::function<void(ResItem*) > cb)
{
	return true;
}

