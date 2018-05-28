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
using namespace std;

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

    glfwTerminate();
    return 0;
}
