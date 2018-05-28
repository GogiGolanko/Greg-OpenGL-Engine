//============================================================================
// Name        : Greg-OpenGL-Engine.cpp
// Author      : Greg
// Version     : 1.0
// Copyright   : Copyright c by Greg
// Description : OpenGL Engine
//============================================================================
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
using namespace std;

#include "Utils.h"
using namespace utils;

static GLuint CompileShader(GLenum type, const string source) {
	GLuint id = glCreateShader(type);
	const char * src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char * message = new char[lenght];
		glGetShaderInfoLog(id, lenght, &lenght, message);
		cout << message << endl;
		delete message;
	}

	return id;
}


static GLuint CreateShader(const string vertexShader, const string fragmentShader) {
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

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

    //glewExperimental = GL_TRUE;
    GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  /* Problem: glewInit failed, something is seriously wrong. */
	  cout << "Error: " << glewGetErrorString(err) << endl;

	}

	cout << "Status: Using GLEW: " << glewGetString(GLEW_VERSION) << endl
		 << "Version of GLFW: " << glfwGetVersionString() << endl
		 << "Company: " << glGetString(GL_VENDOR) << endl
		 << "Name of the renderer: " << glGetString(GL_RENDERER) << endl
		 << "Version of release: " << glGetString(GL_VERSION) << endl
		 << "Shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;


	float positions[6] {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	GLuint shader = CreateShader(Utils::get_shader_source("vs0.glsl"), Utils::get_shader_source("fs0.glsl"));
	glUseProgram(shader);

    /* Loop until the user closes the window */
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

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
