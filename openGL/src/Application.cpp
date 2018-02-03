#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

//in modernGL , opengl rendering pipeline consists of two main components: Vertex BUffers and Shaders.
//Vertex Buffer is basically the input which we give to the renderer which is GPU.
/*Shader is just a program sitting at GPU which executes the given buffer(above) according to instructions given.
  Shaders are of many types... here two of em are used-Vertex Shader and Pixel(Fragment shader)
  As in this program we are displaying the triangle so.. the vertices are drawn by the vertex shader so they are called 3 times as there are 3 vertices.
														the area in between of the vertices and the color is filled by fragment shader so it is called much more times.
*/
//check all the functions used in this functions in docs.gl website, the usage can be learned eventually by practice.

static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);			//type contains which shader type and source will be the source code
	const char* src = source.c_str();				//*src points to the source string ,source[0] can also be used instead of c_str();
	glShaderSource(id, 1, &src, nullptr);			
	glCompileShader(id);

	//Error Handling:
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<endl;
		cout << message;
		glDeleteShader(id);
		return 0;
	}
	//above stuff for error handling

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	//attaching both the type of shaders together
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	//some stuff you have to do
	glLinkProgram(program);
	glValidateProgram(program);

	//deleting the shaders after use to save mem... not that important
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
		cout << "Error!" << endl;
	

	//*****VERTEX BUFFER*******:
	float positions[6] = {-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f}; //position of vertices

	unsigned int buffer;//GenBuffers function gets an id and an unsigned int as a parameters
	glGenBuffers(1, &buffer);//declaring that above created buffer will be used in GPU for openGL
	glBindBuffer(GL_ARRAY_BUFFER, buffer);//defining the buffer as array one... it is called binding
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); //info about the data inside the buffer 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	
	//******SHADER********:

	//both shaders will be written as a c++ program and passed to createshader fucntion as strings
	string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location=0) in vec4 position;"			/*the location(starting index of the postion array) is to be given as vec4
														although it is supposed to be vec2 as vertex coord are 2d but that's how it works*/
		"\n"
		"void main()\n"
		"{\n"
		" glpositon=postion;\n"
		"}\n";

	string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location=0) out vec4 color;"											  
		"\n"
		"void main()\n"
		"{\n"
		" color = vec4(1.0,0.0,0.0,0.0);\n"			//RGBA
		"}\n";

	unsigned int shader = CreateShader(vertexShader,fragmentShader);
	glUseProgram(shader);





	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
