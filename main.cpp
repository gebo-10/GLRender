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

static const float vertex_list[] =
{
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
};


static const GLint index_list[] =
{
	0, 1,
	2, 3,
	4, 5,
	6, 7,
	0, 2,
	1, 3,
	4, 6,
	5, 7,
	0, 4,
	1, 5,
	7, 3,
	2, 6
};
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
	SDL_Window	*pWindow = NULL;
	SDL_Renderer*pRenderer = NULL;
	int win_width = 640, win_height = 480;
	// 1. initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL initialize fail:%s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// 2. create window
	pWindow = SDL_CreateWindow("LuaSDL",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (NULL == pWindow)
	{
		printf("Create window fail:%s\n", SDL_GetError());
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(pWindow);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	glewInit();

	initCamera();

	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 10.0);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(10.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Model model;
	model.Import("box.fbx");

	//float tmp[100] = { 0 };
	//memcpy((void *)tmp, loder.mesh.buff.data, loder.mesh.buff.data_size);

	VAO g_vao;
	g_vao.init();
	const aiMesh* paiMesh = model.scene->mMeshes[0];
	cout << "¶¥µãÊý "<<paiMesh->mNumVertices <<endl;

	int index = g_vao.newVBO(paiMesh->mNumVertices * 3*sizeof(float), (void *)paiMesh->mVertices);
	//int index = g_vao.newVBO(sizeof(vertex_list)*sizeof(float),(void *) vertex_list);

	glEnableVertexAttribArray(0);//????vbo
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);
	//
	//	int ele_index[] = { 0, 1, 2, 4,5,6  ,7};
	ShaderProgram SP;
	int programShader = SP.buildShader("vert.txt", "frag.txt");
	glUseProgram(programShader);

	float uv[] = {
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0
	};
	//index = g_vao.newVBO(sizeof(uv), (void *)uv);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	index = g_vao.newVBO(paiMesh->mNumVertices * sizeof(float), (void *)paiMesh->mTextureCoords[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

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
	int loc = glGetUniformLocation(programShader, "a");
	glUniform1f(loc, arg);

	SDL_Surface * img = IMG_Load("f.jpg");

	SDL_Surface* Picturenew = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_ABGR8888, 0);



	GLuint texture_id = 0;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Picturenew->w, Picturenew->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Picturenew->pixels);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glUniform1f(glGetUniformLocation(programShader, "tex"), 0);





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


		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0, 0.0);// glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, -0.5f);

		glTexCoord2f(1.0, 0.0);// glColor3f(1.0f,0.0f,0.0f);  
		glVertex3f(-1.0f, -1.0f, 2.0f);

		glTexCoord2f(0.0, 1.0); //glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -0.5f);
		glEnd();





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