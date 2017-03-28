//#include <stdio.h>
//#include<Model.hpp>
//
//
//int main()
//{
//	printf("Hello World!\n");
//	Model model;
//	model.Import("spider.fbx");
//	model.Import("spider.fbx");
//	getchar();
//	return 0;
//}


#include <stdio.h>
#include <GL/glew.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <Camera.hpp>
#include<Model.hpp>
#include<VAO.hpp>
#include <VBO.hpp>
#include <ShaderProgram.hpp>
#include<Material.hpp>
#include <App.hpp>
//extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }
//#pragma comment(lib, "legacy_stdio_definitions.lib") 

#include<vector>

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

Camera *camera;
void initCamera(){
	Vector3d pos(0.0, 0.0, 12.0);
	Vector3d target(0.0, 0.0, 0.0);
	Vector3d up(0.0, 1.0, 0.0);
	camera = new Camera(pos, target, up);

}


void RotateX(float angle)
{
	float d = camera->getDist();
	int cnt = 100;
	float theta = angle / cnt;
	float slide_d = -2 * d*sin(theta*3.14159265 / 360);
	camera->yaw(theta / 2);
	for (; cnt != 0; --cnt)
	{
		camera->slide(slide_d, 0, 0);
		camera->yaw(theta);
	}
	camera->yaw(-theta / 2);
}

void RotateY(float angle)
{
	float d = camera->getDist();
	int cnt = 100;
	float theta = angle / cnt;
	float slide_d = 2 * d*sin(theta*3.14159265 / 360);
	camera->pitch(theta / 2);
	for (; cnt != 0; --cnt)
	{
		camera->slide(0, slide_d, 0);
		camera->pitch(theta);
	}
	camera->pitch(-theta / 2);
}

int main(int argc, char* args[])
{
	int win_width = 500, win_height = 500;
	App app;
	app.Init("test", win_width, win_height);
	app.Start()

	initCamera();
	Model model;
	model.Import("box.fbx");


	Metarial metarial;
	metarial.InitShader("vert.txt", "frag.txt");
	metarial.RegTexture("f.jpg");
	metarial.Bind();

	VAO g_vao;
	g_vao.init();
	const aiMesh* paiMesh = model.scene->mMeshes[0];
	cout << "顶点数 "<<paiMesh->mNumVertices <<endl;

	int index = g_vao.newVBO(paiMesh->mNumVertices * 3*sizeof(float), (void *)paiMesh->mVertices);
	//int index = g_vao.newVBO(sizeof(vertex_list)*sizeof(float),(void *) vertex_list);

	glEnableVertexAttribArray(0);//????vbo
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);
	
	cout << "是否纹理坐标：" << paiMesh->HasTextureCoords(0) << endl;
	vector<float> uv;
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pTexCoord =&(paiMesh->mTextureCoords[0][i]);
		uv.push_back(pTexCoord->x);
		uv.push_back(pTexCoord->y);
	}
	//const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
	index = g_vao.newVBO(uv.size() * sizeof(float), (void *)&uv[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
	//http://wiki.jikexueyuan.com/project/modern-opengl-tutorial/tutorial22.html
	//http://assimp.sourceforge.net/lib_html/structai_mesh.html

	vector<int> Indices;
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	g_vao.initEBO(Indices.size() * sizeof(int), (void *)&Indices[0]);

	float arg = 1.0;
	int loc = glGetUniformLocation(metarial.shader.id, "a");
	glUniform1f(loc, arg);



	glViewport(0, 0, (GLint)win_width, (GLint)win_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)win_width / (GLfloat)win_height, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 12.0, 0.0, 0.0, 0, 0.0, 1.0, 0.0);


	//glVertexAttrib1f(loc, 1.0);
	//glEnableVertexAttribArray(loc);
	//glVertexAttribPointer(loc, 1, GL_FLOAT, 0, 0, &arg);

	//	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	//	SDL_RenderClear(pRenderer);

	//	SDL_RenderPresent(pRenderer);

	//	glTranslatef(0.0f, 0.0f, -20.0f);




	//	SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, img);
	//	renderTexture(texture, pRenderer, 0, 0);
	//	SDL_RenderPresent(pRenderer);

	//	glUseProgram(0);




	bool quit = false;
	int x = 0, y = 0;
	Vector2i lastPos;
	int dx, dy;
	SDL_Event e;
	while (!quit){
		while (SDL_PollEvent(&e)){

			switch (e.type){
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE: quit = true; break;
				case SDLK_x: x = x + 1; break;
				case SDLK_y: y = y - 1; break;

				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				lastPos << e.button.x, e.button.y;
				if (e.button.button == SDL_BUTTON_LEFT){

				}
				if (e.button.button == SDL_BUTTON_RIGHT){

				}
				if (e.button.button == SDL_BUTTON_MIDDLE){

				}
				break;
			case SDL_MOUSEMOTION:
				dx = e.button.x - lastPos.x();
				dy = e.button.y - lastPos.y();

				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					RotateX(dx);
					RotateY(dy);
					break;
				case SDL_BUTTON_RIGHT:
					camera->roll(dx);
					break;
				case SDL_BUTTON_MIDDLE:
					camera->slide(-dx, dy, 0);
					break;
				}

				lastPos << e.button.x, e.button.y;
				break;
			case SDL_MOUSEWHEEL:

				camera->slide(0, 0, -e.wheel.y);
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);






		arg = (arg + 0.1);
		int tmpint = (int)arg;
		arg = arg - tmpint;
		glUniform1f(loc, arg);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		camera->setModelViewMatrix();


		//glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, Indices.size() , GL_UNSIGNED_INT, 0);//GL_LINES GL_LINE_LOOP


		SDL_GL_SwapWindow(pWindow);
		SDL_Delay(100);

	}

	SDL_Quit();
	return 1;
}