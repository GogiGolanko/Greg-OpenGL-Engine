//============================================================================
// Name        : Greg-OpenGL-Engine.cpp
// Author      : Greg
// Version     : 1.0
// Copyright   : Copyright c by Greg
// Description : OpenGL Engine
//============================================================================
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
using namespace std;

#include "Utils.h"
using namespace glUtils;

#include "Debug.h"
using namespace glDebug;

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
		delete []message;
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

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwDefaultWindowHints();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //glewExperimental = GL_TRUE;
    GLenum err = glewInit();
	if (GLEW_OK != err) {
	  /* Problem: glewInit failed, something is seriously wrong. */
	  cout << "Error: " << glewGetErrorString(err) << endl;

	}

	DebugOutput* debug = new DebugOutput();

	cout << "Status: Using GLEW: " << glewGetString(GLEW_VERSION) << endl
		 << "Version of GLFW: " << glfwGetVersionString() << endl
		 << "Company: " << glGetString(GL_VENDOR) << endl
		 << "Name of the renderer: " << glGetString(GL_RENDERER) << endl
		 << "Version of release: " << glGetString(GL_VERSION) << endl
		 << "Shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;


	float positions[] {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[] {
		0, 1, 2,
		2, 3, 0
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	GLuint shader = CreateShader(Utils::get_shader_source("vs0.glsl"), Utils::get_shader_source("fs0.glsl"));
	GLint location = glGetUniformLocation(shader, "u_Color");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	float r = 0.0f, inc = 0.05f;
	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        if (r > 1.0f) {
        	inc = -0.05f;
        } else if (r <= 0.0f) {
        	inc = 0.05;
        }

        r += inc;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete debug;
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
