#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//in modernGL , opengl rendering pipeline consists of two main components: Vertex BUffers and Shaders.
//Vertex Buffer is basically the input which we give to the renderer which is GPU.
/*Shader is just a program sitting at GPU which executes the given buffer(above) according to instructions given.
  Shaders are of many types... here two of em are used-Vertex Shader and Pixel(Fragment shader)
  As in this program we are displaying the triangle so.. the vertices are drawn by the vertex shader so they are called 3 times as there are 3 vertices.
														the area in between of the vertices and the color is filled by fragment shader so it is called much more times.
*/
//check all the functions used in this functions in docs.gl website, the usage can be learned eventually by practice.


static string parseShader(string filepath) {
	
	ifstream stream (filepath);
	string line;
	
	try {
		stream.open(filepath);
		stringstream s;
		s << stream.rdbuf();
		stream.close();
		line=s.str();
	}
	catch (ifstream::failure e) {
		cout << "ERROR" << endl;
	}
	return line;
}



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

	glfwSwapInterval(1);	//setting the frame acc to the system

	if (glewInit() != GLEW_OK)
		cout << "Error!" << endl;
	



	//*****VERTEX BUFFER*******:
	float positions[] = {
		-0.5f,-0.5f,
		0.5f,-0.5f,
		0.5f,0.5f,
		-0.5f,0.5f
	}; //position of vertices

	unsigned int indices[] = {	//So, Triangle is the basic element that can be used in a GPU, so every shape have to be made with triangles.
		0, 1 ,2 ,				//But doing that will result in creating so many vertices and mem waste.
		2, 3, 0					// and bcoz of that indices are used which are assigned to each vertex so that they can be used again and again.
	};

	unsigned int buffer;//GenBuffers function gets an id and an unsigned int as a parameters
	glGenBuffers(1, &buffer);//declaring that above created buffer will be used in GPU for openGL
	glBindBuffer(GL_ARRAY_BUFFER, buffer);//defining the buffer as array one... it is called binding
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 *sizeof(float), positions, GL_STATIC_DRAW); //info about the data inside the buffer 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	//Now same thing for Index buffers
	unsigned int index_buffer;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW); 







	//******SHADER********:
	string ver =  parseShader("Shaders/Vertex.shader");
	string frag = parseShader("Shaders/fragment.shader");
	unsigned int shader = CreateShader(ver,frag);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_color");
	


	float r = 0.0f;
	float inc = 0.05f;
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform4f(location, r, 1.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if (r > 1.0f)
			inc = -0.05f;
		else if(r < 0.0f)
			inc = 0.05f;

		r += inc;


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}
