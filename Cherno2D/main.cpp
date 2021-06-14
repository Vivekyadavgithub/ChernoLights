#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h" 
#include "Shader.h"
#include "Texture.h"


void processInput(GLFWwindow* window);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
	GLFWwindow* window;

	if (!glfwInit()) return -1;
 
	
	window = glfwCreateWindow(1980, 1080, "hello", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!\n" << std::endl;
	}
	
	std::cout << glGetString(GL_VERSION);
	
	{
		float positions[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0

		};
		
		VertexArray va;
		VertexBuffer vbo(positions,  6 * 9 * 6 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vbo, layout);

		IndexBuffer ibo(indices, 6);

		
		Shader shader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/Basic.shader");
		shader.Bind();
		shader.Unbind();
		//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		Shader lightShader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/lights.shader");
		lightShader.Bind();
		lightShader.Unbind();
		shader.Bind();
		Texture texture("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/container.jpg");
		texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		vbo.Unbind();
		ibo.Unbind();
		shader.Unbind();

		Renderer renderer;
		shader.Bind();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1980 / (float)1080, 0.1f, 100.0f);
	    shader.SetUniformMat4("projection", projection);
		shader.Unbind();
		float angle = 20.0f * 3;
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();
			if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
				angle += 20.0f;
			processInput(window);

			double xpos = 0, ypos = 0;
			glfwGetCursorPos(window, &xpos, &ypos);
			shader.Bind();
			glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			shader.SetUniformMat4("view", view);
			glm::mat4 model = glm::mat4(1.0f);
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetUniformMat4("model", model);
			float lightX = 2.0f * sin(glfwGetTime());
			float lightY = -0.3f;
			float lightZ = 1.5f * cos(glfwGetTime());
			glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
			//shader.SetUniform3fv("lightPos", 1, glm::vec3(xpos, ypos, ypos - xpos));
			shader.SetUniform3fv("viewPos", 1, lightPos);
			//shader.SetUniform4f("u_Color", 0.0f, 1.0f, 1.0f, 1.0f);
			renderer.Draw(va, ibo, shader);
			shader.Unbind();
			
			lightShader.Bind();
			
			model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
			model = glm::scale(model, {0.2, 0.2, 0.2});
			lightShader.SetUniformMat4("model", model);
			lightShader.SetUniformMat4("projection", projection);
			lightShader.SetUniformMat4("view", view);
			
			renderer.Draw(va, ibo, lightShader);
			lightShader.Unbind();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	
	glfwTerminate();

	return 0;
} 

void processInput(GLFWwindow* window)
{
	const float cameraSpeed = 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}