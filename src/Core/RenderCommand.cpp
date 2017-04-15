#include <RenderEngine.h>
#include <RenderCommand.h>
#include <App.h>

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
void RcmdMesh::Init(Mesh *mesh, MaterialPtr material)
{
	this->mesh = mesh;
	this->material = material;
	ChangeStatus(OBJ_INITED);
}

void RcmdMesh::Deal(RenderEngine * render)
{
	render->CatchError();
	kmMat4 matp;
	kmMat4 mat;
	//glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//±£´æÉãÏñ»ú¾ØÕó

	glMultMatrixf((*transform).mat);//µ±Ç°ÊÓÍ¼¾ØÕó ½áºÏ Ó°Ïì±¾´ÎäÖÈ¾

	//kmMat4Translation(&mat, 0, 0, -10);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.mat);
	glGetFloatv(GL_PROJECTION_MATRIX, matp.mat);
	
	glUseProgram(material->shader->id);

	int local=glGetUniformLocation(material->shader->id, "MV");

	int local3 = glGetUniformLocation(material->shader->id, "P");

	int local2 = glGetUniformLocation(material->shader->id, "a");

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
	glPopMatrix();//»Ö¸´ÉãÏñ»ú¾ØÕó
	if (render->CatchError() > 0)
	{
		return;
	}

	
}
/////////////////////////////////////////////////////////////////////////////////////////
void RcmdLine::Init(vector <kmVec3> vertex, Color color)
{
	this->vertex = vertex;
	this->color = color;
	App::Instance()->resource.GetRes("line.mtl", [=](ResPtr res) {
		this->material = static_pointer_cast<Material>(res);
		this->ChangeStatus(OBJ_INITED);
	});
}

void RcmdLine::Deal(RenderEngine * render)
{
	if (this->CmdInited() != OBJ_INITED)
	{
		return;
	}
	if (render->CatchError() > 0)
	{
		return;
	}
	

	glUseProgram(material->shader->id);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();//±£´æÉãÏñ»ú¾ØÕó
	glLineWidth(1);


	kmMat4 matp;
	kmMat4 mat;
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.mat);
	glGetFloatv(GL_PROJECTION_MATRIX, matp.mat);
	int local = glGetUniformLocation(material->shader->id, "MV");

	int localp = glGetUniformLocation(material->shader->id, "P");

	glUniformMatrix4fv(local, 1, GL_FALSE, mat.mat);
	glUniformMatrix4fv(localp, 1, GL_FALSE, matp.mat);
	
	//glColor3f(0.2, 0.4, 0.6);


	render->vao.UpdateData(0, vertex.size() * 3 * sizeof(float), (void *)&vertex[0]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);
	
	glDrawArrays(GL_LINES, 0, vertex.size() * 3);
	glPopMatrix();//»Ö¸´ÉãÏñ»ú¾ØÕó
	if (render->CatchError() > 0)
	{
		return;
	}
}
