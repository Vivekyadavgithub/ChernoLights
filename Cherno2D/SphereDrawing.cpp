#include "SphereDrawing.h"
#include <iostream>

#include "Vendor/ImGUI/imgui.h"
#include "Vendor/ImGUI/imgui_impl_glfw_gl3.h"

SphereDrawing::SphereDrawing(int SectorCount, int StackCount, float radius)
    :
    m_SectorCount(SectorCount),
    m_StackCount(StackCount),
    m_Radius(radius)
{
    setUpCoordinates();
    setVertexBuffer();
    getIndices();
}

void SphereDrawing::setUpCoordinates()
{
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / m_Radius;    // vertex normal
    float s, t;

    float sectorStep = 2 * PI / m_SectorCount;
    float stackStep = PI / m_StackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= m_StackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = m_Radius * cosf(stackAngle);             // r * cos(u)
        z = m_Radius * sinf(stackAngle);              // r * sin(u)

        // add (m_SectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= m_SectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / m_SectorCount;
            t = (float)i / m_StackCount;
            texCoords.push_back(s);
            texCoords.push_back(t);
        }
    }
}

void SphereDrawing::setVertexBuffer()
{
    VertexBuffer vbo(&vertices[0], 4 * vertices.size());
    VertexBufferLayout layout;
    layout.Push<float>(3);
    va.AddBuffer(vbo, layout);
    va.Unbind();
}

void SphereDrawing::getIndices()
{
    unsigned int k1, k2;
    for (int i = 0; i < m_StackCount; ++i)
    {
        k1 = i * (m_SectorCount + 1);     // beginning of current stack
        k2 = k1 + m_SectorCount + 1;      // beginning of next stack

        for (int j = 0; j < m_SectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (m_StackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

            // store indices for lines
            // vertical lines for all stacks, k1 => k2
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }
        }
    }
}

void SphereDrawing::setIndexBuffer()
{
    
}

void SphereDrawing::setShaderPath(const std::string& path, const std::string& name)
{
    shaderPath = path;
    shaderName = name;
}

void SphereDrawing::setUniforms(glm::mat4 model, glm::mat4 projection, glm::mat4 view)
{
    va.Bind();
    Shader shader(shaderPath, shaderName);
    shader.Bind();
    shader.SetUniformMat4("model", model);
    shader.SetUniformMat4("projection", projection);
    shader.SetUniformMat4("view", view);
 
 //   
    //IndexBuffer ibo(&lineIndices[0], lineIndices.size());
    //ibo.Bind();
    //glDrawElements(GL_LINES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
    //ibo.Unbind();
    IndexBuffer ib(&indices[0], indices.size());
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
   // glDrawElements(GL_LINES, ibo.GetCount() + 4, GL_UNSIGNED_INT, nullptr);

   // glDrawArrays(GL_LINES, 0, vertices.size());
    shader.Unbind();
    ib.Unbind();
    va.Unbind();
}
void SphereDrawing::draw()
{
    for (int i = 0; i < vertices.size(); i+= 3)
    {
        std::cout << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n";
    }
}

void SphereDrawing::setUpGui()
{
    /*ImGui::Begin("sphere debug");
    ImGui_ImplGlfwGL3_NewFrame();
    {
        
        
        ImGui::Text("Application average ");

        //std::cout << color[0] << " " << color[1] << " " << color[2] << "\n";
        //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
        //ImGui::Checkbox("Another Window", &show_another_window);

        //if (ImGui::Button("Ok"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            //counter++;
        //ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);
    }
  
    ImGui::End();*/
}
