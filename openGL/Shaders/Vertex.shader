//both shaders will be written as a c++ program and passed to createshader fucntion as strings
#version 330 core

layout(location=0) in vec4 position;			/*the location(starting index of the postion array) is to be given as vec4
												although it is supposed to be vec2 as vertex coord are 2d but that's how it works*/
	
	void main()
	{
	 gl_Position=position;
	}



