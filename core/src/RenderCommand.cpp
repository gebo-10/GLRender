#include <RenderEngine.h>
#include <RenderCommand.h>


void RenderCommand::Do(RenderEngine * render)
{
	Before();
	Deal(render);
	After();
}

void RenderCommand::Before()
{

}

void RenderCommand::Deal(RenderEngine * render)
{

}

void RenderCommand::After()
{

}

///////////////////////////////////////////////////////////////////
void RcmdMesh::Init(Mesh *mesh, Material *material)
{
	this->mesh = mesh;
	this->material = material;
}

void RcmdMesh::Deal(RenderEngine * render)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//保存摄像机矩阵
	glMultMatrixf((*transform).mat);//当前视图矩阵 结合 影响本次渲染

	render->vao.UpdateData(0, mesh->vertex.size() *sizeof(float), (void *)&mesh->vertex[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);

	render->vao.UpdateData(1, mesh->uv.size() *sizeof(float), (void *)&mesh->uv[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	render->vao.UpdateData(2, mesh->index.size() * sizeof(int), (void *)&mesh->index[0]);

	glDrawElements(GL_TRIANGLES, mesh->index.size(), GL_UNSIGNED_INT, 0);
	glPopMatrix();//恢复摄像机矩阵
}
/////////////////////////////////////////////////////////////////////////////////////////
void RcmdLine::Init(vector <kmVec3> vertex, Color color)
{
	this->vertex = vertex;
	this->color = color;
}

void RcmdLine::Deal(RenderEngine * render)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//保存摄像机矩阵
	//glLoadIdentity();
	//glMultMatrixf((*transform).mat);//当前视图矩阵 结合 影响本次渲染
	glLineWidth(2);
	//glVertexPointer(2, GL_FLOAT, 0,&vertex[0]);

	//glEnableClientState(GL_COLOR_ARRAY);//启用颜色数组
	//float color[3] = { 0.5, 0.5, 0.5 };
	//glColorPointer(3, GL_FLOAT, 0, color);

	//glDrawArrays(GL_LINES, 0, vertex.size() * 3);

	glColor3f(0.2,0.4,0.6);

	float ver[2000] = { 0 };
	for (int i = 0; i < vertex.size();i++)
	{
		ver[i * 3 + 0] = vertex[i].x;
		ver[i * 3 + 1] = vertex[i].y;
		ver[i * 3 + 2] = vertex[i].z;
	}
	render->vao.UpdateData(0, vertex.size() * 3 * sizeof(float), (void *)&ver[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);

	unsigned int ebo[800];
	for (int i = 0; i < 800; i++)
	{
		ebo[i] = i;
	}
	render->vao.UpdateData(2, 800*sizeof(unsigned int), (void *)&ebo[0]);

	glDrawElements(GL_POLYGON, 12, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_LINES, 0, vertex.size() * 3);
	glPopMatrix();//恢复摄像机矩阵
}
