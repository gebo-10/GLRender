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
	glPushMatrix();//�������������
	glMultMatrixf((*transform).mat);//��ǰ��ͼ���� ��� Ӱ�챾����Ⱦ

	render->vao.UpdateData(0, mesh->vertex.size() *sizeof(float), (void *)&mesh->vertex[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);

	render->vao.UpdateData(1, mesh->uv.size() *sizeof(float), (void *)&mesh->uv[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	render->vao.UpdateData(2, mesh->index.size() * sizeof(int), (void *)&mesh->index[0]);

	glDrawElements(GL_TRIANGLES, mesh->index.size(), GL_UNSIGNED_INT, 0);
	glPopMatrix();//�ָ����������
}
