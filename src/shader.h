#ifndef SHADER_H
#define SHADER_H

#include <direct.h>
#include <glad.h>
#include <unistd.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
   public:
    unsigned int ID;
    Shader(){};
    Shader& use();
    void compile(const char* vertex_source, const char* fragment_source, const char* geometry_source = nullptr);
    void set_float(const char* name, float value, bool use_shader = false);
    void set_integer(const char* name, int value, bool use_shader = false);
    void set_vector2f(const char* name, const glm::vec2& value, bool use_shader = false);
    void set_vector2f(const char* name, float x, float y, bool use_shader = false);
    void set_vector3f(const char* name, const glm::vec3& value, bool use_shader = false);
    void set_vector3f(const char* name, float x, float y, float z, bool use_shader = false);
    void set_vector4f(const char* name, const glm::vec4& value, bool use_shader = false);
    void set_vector4f(const char* name, float x, float y, float z, float w, bool use_shader = false);
    void set_matrix4(const char* name, const glm::mat4& value, bool use_shader = false);

   private:
    void check_compile_errors(unsigned int object, std::string type);
};

#endif