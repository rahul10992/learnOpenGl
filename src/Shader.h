//
// Created by Rahul on 7/4/24.
//
// Created by Rahul on 7/4/24.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderType.h"

class Shader {

public:
    // program ID
    unsigned int ID;
    ShaderType shaderType;

    // ctor
    Shader(const char* vertexPath, const char* fragmentPath);

    // use/activate shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};


#endif //HELLO_WINDOW_SHADER_H
