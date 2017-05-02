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

	ShaderPtr d_shader = make_shared<Shader>();


	string vert_file = root + "vert.txt";
	d_shader->BuildVertexShader(file.ReadTextFileSync(vert_file.c_str()) );

	string frag_file = root + "frag.txt";
	d_shader->BuildFragShader(file.ReadTextFileSync(frag_file.c_str()));

	d_shader->BuildProgram();
	default_shader = d_shader;

	TexturePtr d_texure= make_shared<Texture>();
	d_texure->Init(root+"Texure/pure.png");
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
	}
	else
	{
		file.OpenFile(res_root + name, [=](FileWork * work) {
			ResItem * item;

			if (name.find(".shader") != string::npos)
			{
				item = new Shader;
			}
			else if (name.find(".png") != string::npos || (name.find(".jpg") != string::npos) )
			{
				item = new Texture;
			}
			else if (name.find(".mtl") != string::npos)
			{
				item = new Material;
			}
			else
			{
				item = new ResItem;
			}


			item->buff = work->buff;
			item->size = work->size;
			item->filename = name;

			item->Init();

			ResPtr ptr(item, [=](ResItem * res) {
				cout << "Res decache:" << res->filename << endl;
				this->DeCache(res->filename);
				delete res;
			});//make_shared 不支持删除器 无法优化内存分配
			
			cb(ptr);
			this->Cache(name, ptr);
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

