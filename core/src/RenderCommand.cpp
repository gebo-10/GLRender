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
	render->CatchError();
	kmMat4 matp;
	kmMat4 mat;
	//glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//�������������

	glMultMatrixf((*transform).mat);//��ǰ��ͼ���� ��� Ӱ�챾����Ⱦ

	//kmMat4Translation(&mat, 0, 0, -10);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.mat);
	glGetFloatv(GL_PROJECTION_MATRIX, matp.mat);
	
	glUseProgram(material->shader.id);

	int local=glGetUniformLocation(material->shader.id, "MV");

	int local3 = glGetUniformLocation(material->shader.id, "P");

	int local2 = glGetUniformLocation(material->shader.id, "a");

	glUniform1f(local2, 1.0);
	glUniformMatrix4fv(local, 1, GL_FALSE, mat.mat);
	glUniformMatrix4fv(local3, 1, GL_FALSE, matp.mat);

	

	render->vao.UpdateData(0, mesh->vertex.size() *sizeof(float), (void *)&mesh->vertex[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);

	render->vao.UpdateData(1, mesh->uv.size() *sizeof(float), (void *)&mesh->uv[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	render->vao.UpdateData(2, mesh->index.size() * sizeof(int), (void *)&mesh->index[0]);

	glDrawElements(GL_TRIANGLES, mesh->index.size(), GL_UNSIGNED_INT, 0);
	glPopMatrix();//�ָ����������
	if (render->CatchError() > 0)
	{
		int a = 1;
		return;
	}

	
}
/////////////////////////////////////////////////////////////////////////////////////////
void RcmdLine::Init(vector <kmVec3> vertex, Color color)
{
	this->vertex = vertex;
	this->color = color;
}

void RcmdLine::Deal(RenderEngine * render)
{
	render->CatchError();
	return;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//�������������
	glLineWidth(1);

/*
	kmMat4 matp;
	kmMat4 mat;
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.mat);
	glGetFloatv(GL_PROJECTION_MATRIX, matp.mat);
	int local = glGetUniformLocation(material->shader.id, "MV");

	int local3 = glGetUniformLocation(material->shader.id, "P");

	int local2 = glGetUniformLocation(material->shader.id, "a");

	glUniform1f(local2, 1.0);
	glUniformMatrix4fv(local, 1, GL_FALSE, mat.mat);
	glUniformMatrix4fv(local3, 1, GL_FALSE, matp.mat);
	
*/
	//glColor3f(0.2, 0.4, 0.6);

	render->vao.UpdateData(0, vertex.size() * 3 * sizeof(float), (void *)&vertex[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);

	//glDrawArrays(GL_LINES, 0, vertex.size() * 3);
	glPopMatrix();//�ָ����������
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//LOG(ERROR) << "gl  error";
	}
}
