#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	// program ketika berjalan
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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