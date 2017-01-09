#include <ShaderProgram.hpp>
// 把文本文件 读入数组

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}
char * ShaderProgram::readTextFile(char * file_name){
	char *buffer = 0;
	std::ifstream t;
	int length;
	t.open(file_name, ios::binary);      // open input file  
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  
	buffer = new char[length + 1];    // allocate memory for a buffer of appropriate dimension  
	t.read(buffer, length);       // read the whole file into the buffer  
	buffer[length] = '\0';
	t.close();                    // close file handle  
	return buffer;
}


GLuint ShaderProgram::buildShader(GLchar *vShaderFile, GLchar *fShaderFile)
{
	//1、查看GLSL和OpenGL的版本
	GLuint vShader, fShader;//顶点着色器对象
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion =
		glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "GL Vendor    :" << vendor << endl;
	cout << "GL Renderer  : " << renderer << endl;
	cout << "GL Version (string)  : " << version << endl;
	cout << "GL Version (integer) : " << major << "." << minor << endl;
	cout << "GLSL Version : " << glslVersion << endl;

	//2、编译着色器
	//创建着色器对象：顶点着色器
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//错误检测
	if (0 == vShader)
	{
		cerr << "ERROR : Create vertex shader failed" << endl;
		exit(1);
	}

	//把着色器源代码和着色器对象相关联
	GLchar *vShaderCode = 0;
	vShaderCode = readTextFile(vShaderFile);

	//const GLchar *vShaderCode = " in vec3 VertexPosition;vec4 p2; void main(){ p2 = vec4(VertexPosition,1.0);gl_Position =gl_ModelViewProjectionMatrix * p2;}";
	const GLchar *vCodeArray[1] = { vShaderCode };
	glShaderSource(vShader, 1, vCodeArray, NULL);

	//编译着色器对象
	glCompileShader(vShader);


	//检查编译是否成功
	GLint compileResult;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//得到编译日志长度
		glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//得到日志信息并输出
			glGetShaderInfoLog(vShader, logLen, &written, log);
			cerr << "vertex shader compile log : " << endl;
			cerr << log << endl;
			free(log);//释放空间
		}
	}

	//创建着色器对象：片断着色器
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//错误检测
	if (0 == fShader)
	{
		cerr << "ERROR : Create fragment shader failed" << endl;
		exit(1);
	}

	//把着色器源代码和着色器对象相关联
	GLchar *fShaderCode = 0;// = "out vec4 FragColor;void main(){FragColor = vec4(1.0,0.0,1.0, 1.0);}";
	fShaderCode = readTextFile(fShaderFile);
	const GLchar *fCodeArray[1] = { fShaderCode };
	glShaderSource(fShader, 1, fCodeArray, NULL);

	//编译着色器对象
	glCompileShader(fShader);

	//检查编译是否成功
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//得到编译日志长度
		glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//得到日志信息并输出
			glGetShaderInfoLog(fShader, logLen, &written, log);
			cerr << "fragment shader compile log : " << endl;
			cerr << log << endl;
			free(log);//释放空间
		}
	}

	//3、链接着色器对象
	//创建着色器程序
	GLuint programHandle = glCreateProgram();
	if (!programHandle)
	{
		cerr << "ERROR : create program failed" << endl;
		exit(1);
	}
	//将着色器程序链接到所创建的程序中
	glAttachShader(programHandle, vShader);
	glAttachShader(programHandle, fShader);
	//将这些对象链接成一个可执行程序
	glLinkProgram(programHandle);
	//查询链接的结果
	GLint linkStatus;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &linkStatus);
	if (GL_FALSE == linkStatus)
	{
		cerr << "ERROR : link shader program failed" << endl;
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH,
			&logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen,
				&written, log);
			cerr << "Program log : " << endl;
			cerr << log << endl;
		}
	}
	else//链接成功，在OpenGL管线中使用渲染程序
	{
		cerr << "success" << endl;
		return programHandle;
		//	glUseProgram(programHandle);
	}
	return 0;
}