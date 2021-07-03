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
#include "Model.h"

void processInput(GLFWwindow* window);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
	GLFWwindow* window;

	if (!glfwInit()) return -1;
 
	
	window = glfwCreateWindow(1980, 1080, "Opengl Viewer", NULL, NULL);
	
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
		
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
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

		
		Shader shader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D", "Basic");
		shader.Bind();
		shader.Unbind();
		//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		Shader lightShader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D", "lights");
		lightShader.Bind();
		lightShader.Unbind();
		shader.Bind();
		//Texture texture("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/container.jpg");
		//texture.Bind(0);
		//shader.SetUniform1i("ourTexture", 0);
		va.Unbind();
		vbo.Unbind();
		ibo.Unbind();
		shader.Unbind();
		lightShader.Unbind();

		VertexArray skybox;
		VertexBuffer skyBuffer(skyboxVertices, 6 * 6 * 3 * sizeof(float));
		VertexBufferLayout skyboxLayout;
		skyboxLayout.Push<float>(3);
		skybox.AddBuffer(skyBuffer, skyboxLayout);
		Shader skyboxShader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D", "skybox");
		std::vector<std::string> faces(6);

		faces[0] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/right.jpg";
		faces[1] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/left.jpg";
		faces[2] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/top.jpg";
		faces[3] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/bottom.jpg";
		faces[4] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/front.jpg";
		faces[5] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/back.jpg";

		Texture skyboxTex(faces);
		skyboxTex.Unbind();
		skybox.Unbind();
		skyBuffer.Unbind();
		skyboxShader.Unbind();

		Renderer renderer;
		shader.Bind();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1080 / (float)720 , 0.1f, 100.0f);
	    shader.SetUniformMat4("projection", projection);
		shader.Unbind();

		skyboxShader.Bind();
		skyboxShader.SetUniformMat4("projection", projection);
		skyboxShader.SetUniform1i("skybox", 0);
		skyboxShader.Unbind();

		
		Model assimpModel("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/backpack/backpack.obj");
		Shader assimpModelShader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D", "ModelShader");

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
			
			glDepthFunc(GL_LEQUAL);
			skyboxShader.Bind();
			view = glm::mat4(glm::mat3(view));
			skyboxShader.SetUniformMat4("view", view);
			skyboxTex.BindCubeMap(0);
			renderer.Draw(skybox, ibo, skyboxShader);
			glDepthFunc(GL_LESS);
			model = glm::mat4(1.0f);
			model = glm::scale(model, { 0.1, 0.1, 0.1 });
			assimpModelShader.SetUniformMat4("model", model);
			assimpModelShader.SetUniformMat4("projection", projection);
			assimpModelShader.SetUniformMat4("view", view);
			
			assimpModel.Draw(assimpModelShader);

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