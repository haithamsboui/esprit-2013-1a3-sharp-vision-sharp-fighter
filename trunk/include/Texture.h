#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "includes.h"


typedef struct{
    GLuint ID;
    int w;
    int h;
    char *filename;
} IMAGE;

IMAGE **GlobalTextures; //All Textures stored for cleaning later
int TextureCount; //Number of textures

//contains printscreen in black and white
IMAGE *screenimage;

//Load Image from file
IMAGE* load_image(char *filename);

//Add image to global list
void AddImageToList(IMAGE* img);
//Remove image from global list
void RemoveImageFromList(IMAGE* img);


//For resolution change :
//Remove images from opengl memory
void KillTextures();
//reload images to opengl memory
void RefreshGLTextures();


#endif // TEXTURE_H_INCLUDED
