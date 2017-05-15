#include <ResourceManager.h>
#include <Shader.h>
#include <Material.h>
#include <Texture.h>
ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::Init(string root)
{
	res_root = root;

	file.Init();


	default_shader = static_pointer_cast<Shader>(GetResSync("System/default.shader"));
	default_texure = static_pointer_cast<Texture>(GetResSync("System/default.png"));
	default_material = static_pointer_cast<Material>(GetResSync("System/default.mtl"));

	//ResPtr shader_common_header = GetResSync("System/shader_common");

	return true;

}

void ResourceManager::Update(Uint32 delta)
{
	file.Update(delta);
}

bool ResourceManager::Cache(string filename, ResPtr res)
{
	weak_ptr<ResItem> wptr(res);
	this->cache[filename] = wptr;
	return true;
}

bool ResourceManager::DeCache(string filename)
{
	auto itr = cache.find(filename);
	if (itr != cache.end())
	{
		this->cache.erase(itr);
	}
	return true;
}

bool ResourceManager::GetRes(string name, std::function<void(ResPtr) > cb)
{
	auto itr = cache.find(name);
	if (itr!= cache.end() && !itr->second.expired())
	{
		ResPtr ptr = itr->second.lock();
		cb(ptr);
		return true;
	}

	int res_type = RT_NORMAL;
	if (name.find(".shader") != string::npos)
	{
		res_type = RT_SHADER;
	}
	else if (name.find(".png") != string::npos || (name.find(".jpg") != string::npos))
	{
		res_type = RT_TEXTURE;
	}
	else if (name.find(".mtl") != string::npos)
	{
		res_type = RT_MATERIAL;
	}


	file.OpenFile(res_root + name, [=](FileWork * work) {
		ResItem * item=NULL;

		switch (res_type)
		{
		case RT_SHADER:
			item = new Shader;
			break;
		case RT_TEXTURE:
			item = new Texture;
			break;
		case RT_MATERIAL:
			item = new Material;
			break;
		case RT_NORMAL:
			item = new ResItem;
			break;
		default:
			LOG(ERROR) << "Unknow res type"<<endl;
			return false;
			break;
		}

		item->buff = work->buff;
		item->size = work->size;
		item->filename = name;

		item->LoadCallback();

		ResPtr ptr(item, [=](ResItem * res) {
			cout << "Res decache:" << res->filename << endl;
			this->DeCache(res->filename);
			delete res;
		});//make_shared 不支持删除器 无法优化内存分配
			
		cb(ptr);
		this->Cache(name, ptr);
	});

	return true;
}

ResPtr ResourceManager::GetResSync(string name)
{
	int res_type = RT_NORMAL;
	if (name.find(".shader") != string::npos)
	{
		res_type = RT_SHADER;
	}
	else if (name.find(".png") != string::npos || (name.find(".jpg") != string::npos))
	{
		res_type = RT_TEXTURE;
	}
	else if (name.find(".mtl") != string::npos)
	{
		res_type = RT_MATERIAL;
	}

	
	FileWork * work = file.OpenFileSync(res_root + name);
	
	ResItem * item=NULL;
	switch (res_type)
	{
	case RT_SHADER:
		item = new Shader;
		break;
	case RT_TEXTURE:
		item = new Texture;
		break;
	case RT_MATERIAL:
		item = new Material;
		break;
	case RT_NORMAL:
		item = new ResItem;
		break;
	default:
		LOG(ERROR) << "Unknow res type" << endl;
		return false;
		break;
	}

	item->buff = work->buff;
	item->size = work->size;
	item->filename = name;

	item->LoadCallback();

	ResPtr ptr(item, [=](ResItem * res) {
		cout << "Res decache:" << res->filename << endl;
		this->DeCache(res->filename);
		delete res;
	});//make_shared 不支持删除器 无法优化内存分配

	this->Cache(name, ptr);
	return ptr;
}

bool ResourceManager::GetBigRes(string name, std::function<void(ResPtr) > cb)
{
	return true;
}

bool ResourceManager::SaveRes(string name, ResPtr res)
{
	return true;
}

