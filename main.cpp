#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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

	int success;
	char infoLog[512];

	unsigned int vertexShader;
	// mengenerate shader baru
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// menaruh source shader ke vertexshader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compile shader
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "vertext shader failed : " << infoLog << std::endl;
	}


	// untuk frag
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "fragment shader failed : " << infoLog << std::endl;
	}

	// membuat program shader
	unsigned int shaderProgram;
	// mengenerate shader program
	shaderProgram = glCreateProgram();
	// link 2 shader kedalam program shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "shader program failed : " << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	float verticles[] = {
		 0.0f,  0.4f,  0.0f,
		-0.5f, -0.4f,  0.0f,
		 0.5f, -0.4f,  0.0f,
	};

	unsigned int VBO;

	// mengenerate sebuah ID untuk [VBO]
	glGenBuffers(1, &VBO);
	// mengikat gl_array_buffer dengan id [VBO]
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// menaruh data ke dalam gl_array_buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0) ;
	glEnableVertexAttribArray(0);


	// program ketika berjalan
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);

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