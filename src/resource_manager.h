#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <glad.h>

#include <map>
#include <string>

#include "shader.h"
#include "texture.h"

class ResourceManager {
   public:
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;
    static Shader load_shader(const char *vshader_file, const char *fshader_file, const char *gshader_file, std::string name);
    static Shader &get_shader(std::string name);
    static Texture2D load_texture(const char *file, bool alpha, std::string name);
    static Texture2D &get_texture(std::string name);

    static void Clear();

   private:
    ResourceManager(){};
    static Shader load_shader_from_file(const char *vshader_file, const char *fshader_file, const char *gshader_file);
    static Texture2D load_texture_from_file(const char *file, bool alpha);
    static std::string get_path(std::string path_from_src);
};

#endif