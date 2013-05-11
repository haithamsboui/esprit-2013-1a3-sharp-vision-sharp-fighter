#include "includes.h"

IMAGE **GlobalTextures; //All Textures stored for cleaning later
int TextureCount=0; //Number of textures

IMAGE* load_image(char *filename)
{
    int ID,i;
    IMAGE *img=NULL;
    BITMAP *bmp=NULL;

    for(i=0;i<TextureCount;i++){
        if(strcmp(filename,GlobalTextures[i]->filename)==0){
            return GlobalTextures[i];
        }
    }

    bmp=load_png(filename,NULL);
    if (bmp!=NULL)
    {
        ID=allegro_gl_make_texture_ex(AGL_TEXTURE_HAS_ALPHA | AGL_TEXTURE_FLIP,bmp,-1);
        if(ID!=0)
        {
            img=(IMAGE*)malloc(sizeof(IMAGE));
            img->ID=ID;
            img->w=bmp->w;
            img->h=bmp->h;
            img->filename=(char*)malloc(strlen(filename)+1);
            sprintf(img->filename,"%s",filename);
            AddImageToList(img);

        }
        destroy_bitmap(bmp);
    }
    return img;
}

void AddImageToList(IMAGE* img)
{
    TextureCount++;
    GlobalTextures=realloc(GlobalTextures,TextureCount*sizeof(IMAGE*));
    GlobalTextures[TextureCount-1]=img;
}

void RemoveImageFromList(IMAGE* img)
{
    int i,index=-1;
    for(i=0; i<TextureCount && index==-1; i++)
    {
        if(GlobalTextures[i]==img)
        {
            index=i;
        }
    }
    if(index!=-1)
    {
        glDeleteTextures(1,&img->ID);
        free(img->filename);
        free(img);
        for(i=index; i<TextureCount-1; i++)
        {
            GlobalTextures[i]=GlobalTextures[i+1];
        }
        TextureCount--;
        GlobalTextures=realloc(GlobalTextures,TextureCount*sizeof(IMAGE*));
    }
}

void KillTextures(){
    int i;
    for (i=0; i<TextureCount; i++){
        glDeleteTextures(1,&GlobalTextures[i]->ID);
    }

}
void RefreshGLTextures()
{
    int i;
    BITMAP *bmp;
    IMAGE *img;
    for (i=0; i<TextureCount; i++)
    {
        img=GlobalTextures[i];
        bmp=load_png(img->filename,NULL);
        if (bmp!=NULL)
        {
            img->ID=allegro_gl_make_texture_ex(AGL_TEXTURE_HAS_ALPHA | AGL_TEXTURE_FLIP,bmp,-1);
            if(img->ID!=0)
            {
                img->w=bmp->w;
                img->h=bmp->h;
            }
            destroy_bitmap(bmp);
        }
    }
}


IMAGE *screenimage;
void PrintScreen(int colors){
    glDeleteTextures(1,&screenimage->ID);
    free(screenimage);
    screenimage=(IMAGE*)malloc(sizeof(IMAGE));
    glGenTextures (1, &screenimage->ID);
    glBindTexture (GL_TEXTURE_2D, screenimage->ID);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if(colors)
        colors=GL_RGBA;
    else
        colors=GL_LUMINANCE;
    glTexImage2D (GL_TEXTURE_2D, 0, colors, SCREEN_W, SCREEN_H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glCopyTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    glBindTexture (GL_TEXTURE_2D, 0);
    screenimage->w=SCREEN_W;
    screenimage->h=SCREEN_H;
}

/*
TODO : Implimenting blur function.

This technique is used to blur the image. it consist of drawing
the image multiple times with different offsets and transparencies.



 float blur=0.05;
    i=j=FrameCount;
    while(!key[KEY_BACKSPACE] )
    {
        if(j%5==0 && j-i<700)
        {
            draw_image_ex(screenimage,-blur,-blur,100,100,NONE,100);
            draw_image_ex(screenimage,blur,-blur,100,100,NONE,80);
            draw_image_ex(screenimage,-blur,blur,100,100,NONE,60);
            draw_image_ex(screenimage,blur,blur,100,100,NONE,40);
            PrintScreen(FALSE);

            blur-=0.0005;
        }
        else
        {
            draw_image_ex(screenimage,0,0,100,100,NONE,100);

        }
        j=next_frame();
    }
*/
