#include "shader.h"

#include <iostream>

Shader& Shader::use() {
    glUseProgram(ID);
    return *this;
}

void Shader::compile(const char* vertex_source, const char* fragment_source, const char* geometry_source) {
    unsigned int vertex_shader, fragment_shader, geometry_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    check_compile_errors(vertex_shader, "VERTEX");

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    check_compile_errors(fragment_shader, "FRAGMENT");

    if (geometry_source != nullptr) {
        geometry_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(geometry_shader, 1, &geometry_source, NULL);
        glCompileShader(geometry_shader);
        check_compile_errors(geometry_shader, "GEOMETRY");
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    if (geometry_source != nullptr) {
        glAttachShader(ID, geometry_shader);
    }

    glLinkProgram(ID);
    check_compile_errors(ID, "PROGRAM");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (geometry_source != nullptr) {
        glDeleteShader(geometry_shader);
    }
};

void Shader::set_float(const char* name, float value, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform1f(glGetUniformLocation(ID, name), value);
};

void Shader::set_integer(const char* name, int value, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform1i(glGetUniformLocation(ID, name), value);
};

void Shader::set_vector2f(const char* name, const glm::vec2& value, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
};
void Shader::set_vector2f(const char* name, float x, float y, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform2f(glGetUniformLocation(ID, name), x, y);
};

void Shader::set_vector3f(const char* name, const glm::vec3& value, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
};

void Shader::set_vector3f(const char* name, float x, float y, float z, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
};

void Shader::set_vector4f(const char* name, const glm::vec4& value, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
};

void Shader::set_vector4f(const char* name, float x, float y, float z, float w, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
};

void Shader::set_matrix4(const char* name, const glm::mat4& value, bool use_shader) {
    if (use_shader) {
        use();
    }
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
};

void Shader::check_compile_errors(unsigned int object, std::string type) {
    int success;
    char info_log[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, info_log);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << info_log << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, info_log);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                      << info_log << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
};