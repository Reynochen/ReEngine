#include"ModelLoader.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

#include<glm/glm.hpp>

#include"Mesh.hpp"

std::vector<std::string> split(std::string& line, char delim) {
    std::vector<std::string> elems;

    std::stringstream ss(line);
    std::string word;
    while (std::getline(ss, word, delim)) {
        elems.push_back(word);
    }

    return elems;
}

ModelLoader::ModelLoader() {}

void ModelLoader::loadOBJModel(const char* filePath) 
{
    std::vector<glm::vec3> v;
    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;

    std::string line;
    std::vector<std::string> words;
    std::vector<Vertex> vert;

    std::ifstream file;

    file.open(filePath);
    while (std::getline(file, line)) { //Get line
        words = split(line, ' ');

        if (!words[0].compare("v")) {
            v.push_back(glm::vec3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3])));
        }
        else if (!words[0].compare("vt")) {
            vt.push_back(glm::vec2(std::stof(words[1]), std::stof(words[2])));
        }
        else if (!words[0].compare("vn")) {
            vn.push_back(glm::vec3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3])));
        }
        else if (!words[0].compare("f")) {
            readFace(words, v, vt, vn, vert);
        }

    }
    file.close();

    //Loaded success
    this->vertices = new std::vector<Vertex>(vert);
}

void ModelLoader::readFace(std::vector<std::string>&words, std::vector<glm::vec3>&v, std::vector<glm::vec2>&vt, std::vector<glm::vec3>&vn, std::vector<Vertex>& vert) {
    size_t triangleCount = words.size() - 3;

    for (size_t i = 0; i < triangleCount; ++i) {
        readCorner(words[1], v, vt, vn, vert);
        readCorner(words[2 + i], v, vt, vn, vert);
        readCorner(words[3 + i], v, vt, vn, vert);        
    }
}

void ModelLoader::readCorner(std::string& word, std::vector<glm::vec3>&v, std::vector<glm::vec2>&vt, std::vector<glm::vec3>&vn, std::vector<Vertex>& vert) {
    std::vector<std::string> face = split(word, '/');

    //Pos
    glm::vec3 pos = v[std::stol(face[0]) - 1];
    //tex coords
    glm::vec2 tex = vt[std::stol(face[1]) - 1];
    //Normal
    glm::vec3 normal = vn[std::stol(face[2]) - 1];

    vert.push_back(Vertex {pos, tex, normal, glm::vec4(1.f)});
}