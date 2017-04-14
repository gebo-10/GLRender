#ifndef _SCENE_MANAGER_HPP
#define _SCENE_MANAGER_HPP
#include<Common.h>
#include<SceneObject.h>
#include<Camera.h>
#include<vector>
#include <RenderEngine.h>
#include<stack>  
class SceneManager{
public:
	int tag_id;
	SceneObject *root;
	//cameras lights_;用组件方加
public:
	SceneManager();
	~SceneManager();
	void Init();
	int GenTag();
	void Update(Uint32 delta);

	SceneObject * getRoot(){ return root; };
	SceneObject * NewObject();
	bool AddObject(SceneObject * parent, SceneObject * obj);
	
	void VistObj(SceneObject * obj, Uint32 delta);
	void DelObject(SceneObject * obj);
	SceneObject * FindObject(int tag, SceneObject * root=NULL);

public:
	class Iterator
	{
	private:
		stack<int> level_stack;
		int child_index;
		SceneObject * root;
		SceneObject * now;
	public:
		Iterator(SceneObject * root)
		{
			this->root = root;
			now = root;
			child_index = 0;
			level_stack.push(0);
			level_stack.push(0);
		};

		~Iterator()
		{
		};
		SceneObject * GetCurrent(){
			return now;
		};
		void operator++(){
			if (root->children.size()==0)
			{
				now = NULL;
				return;
			}
			else if (root==now){
				now = root->children[0];
				child_index++;
				return;
			}
			GetNext();

		};
		void GetNext(){
			if (now->parent == NULL)
			{
				now = NULL;
			}
			else if (child_index  >= now->parent->children.size())
			{
				level_stack.pop();
				child_index = level_stack.top();
				child_index++;
				
				now = now->parent;
				return GetNext();
			}
			
			else if (now->children.size() > 0)
			{
				now = now->children[0];
				level_stack.push(child_index);
				child_index = 0;
			}
			else if (child_index  < now->parent->children.size())
			{
				now = now->parent->children[child_index];
				child_index++;
			}
		}
		bool IsEnd(){
			return now == NULL;
		};
	};

};
#endif
