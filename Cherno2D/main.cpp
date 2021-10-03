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
#include "SphereDrawing.h"

#include "Vendor/ImGUI/imgui.h"
#include "Vendor/ImGUI/imgui_impl_glfw_gl3.h"

void displayMatrix(glm::mat4 matrix) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::string indent = (matrix[i][j] >= 0) ? " " : "";
			std::cout << indent << matrix[i][j] << "   ";
		}
		std::cout << "\n";
	}
}
void processInput(GLFWwindow* window);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
	GLFWwindow* window;

	if (!glfwInit()) return -1;
 
	
	window = glfwCreateWindow(1920, 1080, "Opengl Viewer", NULL, NULL);
	
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
		
	Texture texture("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/container.png");
	Texture specularMap("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/container_specular.png");
	texture.Bind(0);
	shader.SetUniform1i("material.diffuse", 0);
	texture.Unbind();
	specularMap.Bind(1);
	shader.SetUniform1i("material.specular", 1);
	specularMap.Unbind();
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
	std::vector<std::string> faces2(6);

	faces[0] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/right.jpg";
	faces[1] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/left.jpg";
	faces[2] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/top.jpg";
	faces[3] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/bottom.jpg";
	faces[4] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/front.jpg";
	faces[5] = "C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/skybox/back.jpg";

	faces2[0] = "D:/git/Syl3D/Syl3D/resources/skyboxes/epicbluesunset/right.png";
	faces2[1] = "D:/git/Syl3D/Syl3D/resources/skyboxes/epicbluesunset/left.png";
	faces2[2] = "D:/git/Syl3D/Syl3D/resources/skyboxes/epicbluesunset/top.png";
	faces2[3] = "D:/git/Syl3D/Syl3D/resources/skyboxes/epicbluesunset/bottom.png";
	faces2[4] = "D:/git/Syl3D/Syl3D/resources/skyboxes/epicbluesunset/front.png";
	faces2[5] = "D:/git/Syl3D/Syl3D/resources/skyboxes/epicbluesunset/back.png";
	Texture skyboxTex(faces);
	skyboxTex.Unbind();
	Texture skyboxTex2(faces2);
	skyboxTex2.Unbind();
	skybox.Unbind();
	skyBuffer.Unbind();
	skyboxShader.Unbind();

	Renderer renderer;
	shader.Bind();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1980 / (float)1080, 0.1f, 100.0f);
	shader.SetUniformMat4("projection", projection);
	shader.Unbind();

	skyboxShader.Bind();
	skyboxShader.SetUniformMat4("projection", projection);
	skyboxShader.SetUniform1i("skybox", 0);
	skyboxShader.Unbind();

		
	Model assimpModel("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D/res/backpack/backpack.obj");
	Shader assimpModelShader("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D", "ModelShader");

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	int selectedObject = 0;
	int selectedLight = 0;
	bool show_demo_window = true;
	bool show_another_window = true;
	std::vector<float> color(4, 0.0f);
	std::vector<float> lightDiff(3, 0.0f);
	std::vector<float> Position(3, 0.0f);
	std::vector<float> lightAmb(3, 0.0f);
	std::vector<std::vector<float>> lightPosition(1, {0.f, 0.f, 0.f});
	std::vector<std::vector<float>> objectPosition(1, {0.f, 0.f, 0.f});
	std::vector<float> lightSpec(3, 0.0f);
	std::vector<float> viewPosition(3, 0.0f);
	
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	float angle = 20.0f * 3;
	bool loadModel = false;
	SphereDrawing sphereDrawing(36, 18, 0.5f);
	sphereDrawing.setShaderPath("C:/VisualStudio_Projects/Cherno/Cherno2D/Cherno2D", "Simple");

	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		ImGui_ImplGlfwGL3_NewFrame();
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
			angle += 20.0f;
		processInput(window);
		sphereDrawing.setUpGui();
		double xpos = 0, ypos = 0;
		glfwGetCursorPos(window, &xpos, &ypos);
		shader.Bind();
		texture.Bind();
		specularMap.Bind(1);
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		shader.SetUniformMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);

		shader.SetUniform3fv("viewPos", 1, glm::vec3(viewPosition[0], viewPosition[1], viewPosition[2]));

		for (int i = 0; i < lightPosition.size(); i++) {
			std::string str = "lightPos[";
			char temp = i + '0';
			str += temp;
			str += ']';
			shader.SetUniform3fv(str, 1, glm::vec3(lightPosition[i][0], lightPosition[i][1], lightPosition[i][2]));
		}
			
		shader.SetUniform3fv("light.ambient", 1, glm::vec3(lightAmb[0], lightAmb[1], lightAmb[2]));
		shader.SetUniform3fv("light.diffuse", 1, glm::vec3(lightDiff[0], lightDiff[1], lightDiff[2]));
		shader.SetUniform3fv("light.specular", 1, glm::vec3(lightSpec[0], lightSpec[1], lightSpec[2]));
		shader.SetUniform1i("lightCount", lightPosition.size());
		shader.SetUniform1f("material.shininess", 32.0f);
		
		for (int i = 0; i < objectPosition.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(objectPosition[i][0], objectPosition[i][1], objectPosition[i][2]));
			shader.SetUniformMat4("model", model);
				
			renderer.Draw(va, ibo, shader);
		}

		texture.Unbind();
		specularMap.Unbind();
		shader.Unbind();
			
		lightShader.Bind();
		//model = glm::translate(model, glm::vec3(lightPosition[0][0], lightPosition[0][1], lightPosition[0][2]));
		//model = glm::scale(model, { 1.0, 1.0, 1.0 });
		lightShader.SetUniformMat4("projection", projection);
		lightShader.SetUniformMat4("view", view);

		for (int i = 0; i < lightPosition.size(); i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, { lightPosition[i][0], lightPosition[i][1], lightPosition[i][1] });

			lightShader.SetUniformMat4("model", model);

			renderer.Draw(va, ibo, lightShader);
		}
		lightShader.Unbind();
			
		if (loadModel) {
			assimpModelShader.Bind();
			model = glm::mat4(1.0f);
			model = glm::scale(model, { 1.0, 1.0, 1.0 });
			model = glm::translate(model, glm::vec3(1.0f, 1.0f, -3.0f));

			assimpModelShader.SetUniformMat4("model", model);
			assimpModelShader.SetUniformMat4("projection", projection);
			assimpModelShader.SetUniformMat4("view", view);

			assimpModel.Draw(assimpModelShader);
			assimpModelShader.Unbind();
		}
		model = glm::mat4(1.0f);
		model = glm::scale(model, { 1.0, 1.0, 1.0 });
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -5.0f));
		//sphereDrawing.setUniforms(model, projection, view);
		//sphereDrawing.draw();
		glDepthFunc(GL_LEQUAL);

		skyboxShader.Bind();
		view = glm::mat4(glm::mat3(view));
		skyboxShader.SetUniformMat4("view", view);
		skyboxTex.BindCubeMap(0);
		//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		renderer.Draw(skybox, ibo, skyboxShader);
		glDepthFunc(GL_LESS);

			
		{
			ImGui::Begin("s debug");
			static float f = 0.0f;
			static int counter = 0;
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
			ImGui::ColorEdit3("Light Ambient", &lightAmb[0]);
			ImGui::SliderFloat3("Light position", &lightPosition[0][0], -10.0f, 10.0f);
			ImGui::SliderFloat3("Object Position", &objectPosition[0][0], -10.0f, 10.0f);
			ImGui::ColorEdit3("Light Specular", &lightSpec[0]);
			ImGui::ColorEdit3("Light Diffuse", &lightDiff[0]);
			ImGui::SliderFloat3("ViewPosition", &viewPosition[0], -10.0f, 10.0f);
			if(ImGui::Button("Add Light", { 75, 25 })) {
				
	
			}
			if (ImGui::Button("Add Objects", { 75, 25 })) {
				
			}
			if(ImGui::Button("Flip Camera", { 75, 25 })) {
				cameraFront.z *= -1;
			}
			if (ImGui::Button("Rotate", { 75, 25 })) {
				cameraFront.x += 0.05f;
				//cameraFront.x = cos(cameraFront.x);
			}
			std::vector<const char*> items;
			items.push_back("--");
			items.push_back("PointLights");
			items.push_back("Objects");
			items.push_back("Orange");
			int selectedItem = 0;
			bool selected[3];
			if (ImGui::Combo("Add items", &selectedItem, &items[0], items.size())) {

				for (int i = 0; i < items.size(); i++)
				{
					//ImGui::Selectable(items[i], &selected[i], ImGuiSelectableFlags_AllowDoubleClick);
					ImGui::Selectable(items[i]);
				}
				if (selectedItem == 1) {
					int index = lightPosition.size() - 1;
					lightPosition.push_back({ lightPosition[index][0] + 3.0f, lightPosition[index][1], lightPosition[index][2] });
				}
				else if (selectedItem == 2) {
					int index = objectPosition.size() - 1;
					objectPosition.push_back({ objectPosition[index][0] + 3.0f, objectPosition[index][1], objectPosition[index][2] });
				}
			}

			std::vector<std::string> objectNames;
			std::vector<const char*> objectNameschar;

			for (int i = 0; i < objectPosition.size(); i++)
			{
				char c = i + '0';
				std::string name = "Object_";
				name += c;
				objectNames.push_back(name);
			}
			for (int i = 0; i < lightPosition.size(); i++)
			{
				char c = i + '0';
				std::string name = "light_";
				name += c;
				objectNames.push_back(name);
			}

			for (auto& it : objectNames) {
				objectNameschar.push_back(it.c_str());
			}
			//for (int i = 0; i < objectNames.size(); i++) std::cout << objectNameschar[i] << "\n";

			{
				ImGui::Begin("Objects");

				static int selectedObject = 0;
				std::vector<bool> select(objectNameschar.size());
				if (ImGui::ListBox("objects", &selectedObject, &objectNameschar[0], objectNameschar.size())) {
					for (int i = 0; i < objectNameschar.size(); i++)
					{
						ImGui::Selectable(objectNameschar[i]);
					}
				}

				if (ImGui::BeginCombo("Objects", "test")){//&selectedObject, &objectNameschar[0], objectNameschar.size())) {

					for (int i = 0; i < objectNames.size(); i++)
					{
						ImGui::Selectable(objectNameschar[i], select[i], ImGuiSelectableFlags_DontClosePopups);
					}
				}

				ImGui::End();
			}
			/**/
			/*ImGui::Text("Application average %.3f ms/frame (%.1f FPS)\n "
				"CameraPos x = %.2f y = %.2f z = %.2f \n"
				"CameraFront x = % .2f y = % .2f z = % .2f",
				1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate, 
				cameraPos.x, cameraPos.y , cameraPos.z,
				cameraFront.x, cameraFront.y, cameraFront.z);*/
			for (int i = 0; i < objectPosition.size(); i++) {
				ImGui::Text(" == %.3f ..", objectPosition[i][0]);
			}
			ImGui::End();
			//std::cout << color[0] << " " << color[1] << " " << color[2] << "\n";
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			//if (ImGui::Button("Ok"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
				//counter++;
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

		}
		{
			ImGui::Begin("debug 2");
			ImGui::Button("ok");
			if (ImGui::Button("Rotate", { 50, 50 }))
			{
				if (cameraPos.z >= 0.0f) {
					cameraFront.z = -1;
					cameraPos.x += 0.05f;
					cameraFront.x = cameraPos.x / 3;
				}
				else {
					cameraPos.x -= 0.05f;
					cameraFront.z = 1;
					cameraFront.x = cameraPos.x / 3;
				}
				cameraPos.z = sqrt(9.0f - (cameraPos.x * cameraPos.x));
			}
			if (ImGui::Button("Load BackPack", { 30, 20 })) {

				loadModel = !loadModel;
			}
			if (ImGui::Button("cameraFacex++", { 100, 50 }))
			{
				cameraFront.x += 0.05f;
			}
			if (ImGui::Button("cameraFacex--", { 100, 50 }))
			{
				cameraFront.x -= 0.05f;
			}
			if (ImGui::Button("cameraFacey++", { 100, 50 }))
			{
				cameraFront.y += 0.05f;
			}
			if (ImGui::Button("cameraFacey--", { 100, 50 }))
			{
				cameraFront.y -= 0.05f;
			}
			if (ImGui::Button("cameraFacez++", { 100, 50 }))
			{
				cameraFront.z += 0.05f;
			}
			if (ImGui::Button("cameraFacez--", { 100, 50 }))
			{
				cameraFront.z -= 0.05f;
			}
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
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