#include "resource_manager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "logger.hpp"
#include "stb_image.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Logger logger("log.txt");

Shader ResourceManager::load_shader(const char *vshader_file, const char *fshader_file, const char *gshader_file, std::string name) {
    Shaders[name] = load_shader_from_file(vshader_file, fshader_file, gshader_file);
    return Shaders[name];
};

Shader &ResourceManager::get_shader(std::string name) {
    return Shaders[name];
};

Texture2D ResourceManager::load_texture(const char *file, bool alpha, std::string name) {
    Textures[name] = load_texture_from_file(file, alpha);
    return Textures[name];
};

Texture2D &ResourceManager::get_texture(std::string name) {
    return Textures[name];
};

void ResourceManager::Clear() {
    for (auto &iter : Shaders) {
        glDeleteProgram(iter.second.ID);
    }
    for (auto &iter : Textures) {
        glDeleteTextures(1, &iter.second.ID);
    }
};

Shader ResourceManager::load_shader_from_file(const char *vshader_file, const char *fshader_file, const char *gshader_file) {
    std::string vsfile = get_path(vshader_file);
    std::string fsfile = get_path(fshader_file);

    std::string vertex_code, fragment_code, geometry_code;
    try {
        std::ifstream vertex_shader_file(vsfile), fragment_shader_file(fsfile);
        std::stringstream vshader_stream, fshader_stream;
        vshader_stream << vertex_shader_file.rdbuf();
        fshader_stream << fragment_shader_file.rdbuf();

        vertex_shader_file.close();
        fragment_shader_file.close();

        vertex_code = vshader_stream.str();
        fragment_code = fshader_stream.str();

        if (gshader_file != nullptr) {
            std::string gsfile = get_path(gshader_file);
            std::ifstream geometry_shader_file(gsfile);
            std::stringstream gshader_stream;
            gshader_stream << geometry_shader_file.rdbuf();
            geometry_shader_file.close();
            geometry_code = gshader_stream.str();
        }
    } catch (std::exception &e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << e.what() << std::endl;
    }

    const char *vshader_code = vertex_code.c_str();
    const char *fshader_code = fragment_code.c_str();
    const char *gshader_code = geometry_code.c_str();

    Shader shader;
    shader.compile(vshader_code, fshader_code, gshader_file == nullptr ? nullptr : gshader_code);
    return shader;
};

Texture2D ResourceManager::load_texture_from_file(const char *file, bool alpha) {
    Texture2D texture;
    if (alpha) {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }
    int width, height, nr_channels;
    unsigned char *data = stbi_load(get_path(file).c_str(), &width, &height, &nr_channels, 0);
    texture.generate(width, height, data);
    stbi_image_free(data);
    return texture;
};

std::string ResourceManager::get_path(std::string path_from_src) {
    char buffer[1024];
    if (_getcwd(buffer, 1024)) {
        return (std::string(buffer) + "\\" + path_from_src);
    } else {
        return "";
    }
}