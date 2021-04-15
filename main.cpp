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
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0

		};

		VertexArray va;
		VertexBuffer vbo(positions, 6 * 6 * 6 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		va.AddBuffer(vbo, layout);

		IndexBuffer ibo(indices, 6);

		/*Assimp::Importer importer;
		std::string path = "D:/game_dev/Blender/cottage_blender.blend";
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}*/
		//std::string directory = path.substr(0, path.find_last_of('/'));

		//processNode(scene->mRootNode, scene);
		
		Shader shader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/Basic.shader");
		shader.Bind();
		shader.Unbind();
		//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		Shader lightShader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/lights.shader");
		lightShader.Bind();
		lightShader.Unbind();
		shader.Bind();
		//Texture texture("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/container.jpg");
		//texture.Bind();
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

			
			shader.Bind();
			glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			shader.SetUniformMat4("view", view);
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetUniformMat4("model", model);
			//shader.SetUniform4f("u_Color", 0.0f, 1.0f, 1.0f, 1.0f);
			renderer.Draw(va, ibo, shader);
			shader.Unbind();
			
			lightShader.Bind();
			model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
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