#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// inisialisasi GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// membuat window program
	GLFWwindow* window = glfwCreateWindow(600, 600, "Learn Opengl", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// menaruh window program yang telah dibuat ke dalam context
	glfwMakeContextCurrent(window);

	// mengecek apakah GLAD telah di inisialisasi
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed initialize GLAD" << std::endl;
		return -1;
	}

	// mereaksi jika program mengalami resize window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader ourShader("vertexShader.glsl", "fragmentShader.glsl");

	float verticles[] = {
		-0.5f,  0.4f,  0.0f,  1.0f,  0.0f,  0.0f,
		-0.5f, -0.4f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.4f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.4f,  0.0f,  1.0f,  1.0f,  0.0f,
	};

	unsigned int indicades[] = {
		0, 1, 2,
		2, 0, 3
	};

	unsigned int VAO{};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO{};
	// mengenerate sebuah ID untuk [VBO]
	glGenBuffers(1, &VBO);
	// mengikat gl_array_buffer dengan id [VBO]
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// menaruh data ke dalam gl_array_buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	unsigned int EBO{};
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicades), indicades, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//int vertexOurColorLoc = glGetUniformLocation(shaderProgram, "ourColor");
	//glUniform4f(vertexOurColorLoc, 1.0f, 1.0f, 0.0f, 0.0f);

	// program ketika berjalan
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();

		//glUniform4f(vertexOurColorLoc, 0.5f, 0.1f, 0.1f, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ourShader.deleteProgram();

	// mematikan program
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
}