#ifndef OBJ_LOADER
#define OBJ_LOADER

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#include<glm/glm.hpp>

#include"Mesh.hpp"

static std::vector<Vertex> loadOBJ(const char* path) 
{
    std::vector<glm::fvec3> vertex_positions;
    std::vector<glm::fvec2> vertex_texcoords;
    std::vector<glm::fvec3> vertex_normals;

    std::vector<GLuint> vertex_position_indices;
    std::vector<GLuint> vertex_texcoord_indices;
    std::vector<GLuint> vertex_normal_indices;

    std::vector<Vertex> vertices;

    std::stringstream ss;
    std::ifstream file(path);

    std::string line;
    std::string prefix = "";

    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLint temp_glint = 0;

    if(!file.is_open()) {
        std::cerr << "ERROR::OBJLOADER::Could not open file.\n";
        return vertices;
    }

    //Read one line at a time
    while(std::getline(file, line)) 
    {
        //Get the prefix of the line
        ss.clear();
        ss.str(line);
        ss >> prefix;
        
        if(prefix == "v") //Vertex pos 
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_positions.push_back(temp_vec3);
        }
        else if(prefix == "vt") //TexCoords
        {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertex_texcoords.push_back(temp_vec2);
        }
        else if(prefix == "vn") //Normal
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_normals.push_back(temp_vec3);
            // std::cout << temp_vec3.x <<'/'<< temp_vec3.y <<'/'<< temp_vec3.z << "\t\t"<<vertex_normals.size()<<'\n';
        }
        else if(prefix == "f")
        {
            int counter = 0;
            while(ss >> temp_glint)
            {
                //Pushing indices
                if(counter == 0)
                    vertex_position_indices.push_back(temp_glint);
                else if(counter == 1)
                    vertex_texcoord_indices.push_back(temp_glint);
                else if(counter == 2)
                    vertex_normal_indices.push_back(temp_glint);
            
                //Handling characters
                if(ss.peek() == '/')
                {
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if(ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }
                //Reset counter
                if(counter > 2)
                    counter = 0;
            }
        }
    }

    //Build final mesh
    vertices.resize(vertex_position_indices.size(), Vertex());

    if(vertex_positions.size() == 0 || vertex_texcoords.size() == 0 || vertex_normals.size() == 0) {
        std::cerr << "ERROR::OBJLOADER::Incorrect OBJ file mesh.\n";
        return vertices;
    } 

    //Load in all indices
    for(size_t i = 0; i < vertices.size(); ++i) 
    {
        vertices[i].position = vertex_positions[vertex_position_indices[i]-1];
        vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indices[i]-1];
        vertices[i].normal = vertex_normals[vertex_normal_indices[i]-1];
        vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
    }    

    std::cout << "Number of vertices: " << vertices.size() << '\n';
    //Loaded success
    return vertices;
}

#endif