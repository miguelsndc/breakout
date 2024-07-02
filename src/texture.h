#ifndef TEXTURE_H
#define TEXTURE_H

class Texture2D {
   public:
    unsigned int ID;
    unsigned int width, height;
    unsigned int internal_format;
    unsigned int image_format;
    unsigned int wrap_s;
    unsigned int wrap_t;
    unsigned int filter_min;
    unsigned int filter_max;

    Texture2D();
    void generate(unsigned int width, unsigned int height, unsigned char* data);
    void bind() const;
};

#endif