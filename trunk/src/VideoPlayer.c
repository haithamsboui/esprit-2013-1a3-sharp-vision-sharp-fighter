#include "includes.h"

int PlayVideo(const char *filename)
{
    float ratio,w,h,x,y;
    APEG_STREAM *stream;
    GLuint tex_id;

    set_volume_per_voice(0);
    apeg_set_display_depth(32);
    apeg_ignore_video(0);
    apeg_ignore_audio(0);
    stream = apeg_open_stream(filename);

    if(!stream)
    {
        allegro_message("APEG Error: %s\n", apeg_error);
        return APEG_ERROR;
    }

    if(!(stream->flags & APEG_HAS_VIDEO))
    {
        allegro_message("No video\n");
        apeg_close_stream(stream);
        return APEG_ERROR;
    }

    // Reset APEG's color tables since we just entered a valid video mode
    apeg_reset_colors(stream);
    voice_set_volume(apeg_get_stream_voice(stream),Music_volume);
    apeg_advance_stream(stream, 0);
    tex_id=allegro_gl_make_texture_ex(AGL_TEXTURE_FLIP,stream->bitmap,-1);
    apeg_reset_stream(stream);

    glBindTexture(GL_TEXTURE_2D, tex_id);

    glColor3f(1, 1, 1);

    apeg_set_audio_bufsize(8192);
    rest(500);

    //aspect ratio
    ratio=fmax((float)stream->w/(float)SCREEN_W , (float)stream->h/(float)SCREEN_H);
    w=(float)stream->w/ratio;
    h=(float)stream->h/ratio;
    x=(float)SCREEN_W/2.0f - (float)w/2.0f;
    y=(float)SCREEN_H/2.0f - (float)h/2.0f;

    //to gl coords
    w=(w/SCREEN_W)*2;
    h=(h/SCREEN_H)*2;
    x=(x/SCREEN_W)*2 -1;
    y=(y/SCREEN_H)*2 -1;
    //;

    //Reset the video timer (it has been running since we opened the mpeg).
    stream->timer = -1;
    while(stream->timer == -1);

    // Get the next video frame

    while(apeg_advance_stream(stream, 0) == APEG_OK)
    {
        // Stop if a key is pressed
        if(AnyKeyPressed(3) || close_button_pressed) //Condition to exit
            break;

        // If the bitmap was updated, update the screen, else mark it as
        // skipped, or just rest a tad
        if(stream->frame_updated > 0)
        {
            // Update texture image data
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, stream->bitmap->w,
                            stream->bitmap->h, GL_RGBA, GL_UNSIGNED_BYTE,
                            stream->bitmap->line[0]);
        }
        else
        {
            // No change yet
            if(stream->frame_updated < 0 && !stream->audio.flushed)
                rest(1);

            continue;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex2f(x+w, -(y+h));

        glTexCoord2f(1, 0);
        glVertex2f(x+w, -y);

        glTexCoord2f(0, 0);
        glVertex2f(x, -y);

        glTexCoord2f(0, 1);
        glVertex2f(x, -(y+h));
        glEnd();

        allegro_gl_flip();
        FrameCount++;
    }

    glDeleteTextures(1,&tex_id);
    apeg_close_stream(stream);
    return APEG_OK;
}

int PlayAudio(const char *filename)
{
    APEG_STREAM *stream;
    apeg_set_audio_bufsize(32768);
    set_volume_per_voice(0);
    stream = apeg_open_stream(filename);

    if(!stream)
    {
        allegro_message("APEG Error: %s\n", apeg_error);
        return APEG_ERROR;
    }

    if(!(stream->flags & APEG_HAS_AUDIO))
    {
        allegro_message("No audio\n");
        apeg_close_stream(stream);
        return APEG_ERROR;
    }
    apeg_ignore_video(1);
    apeg_ignore_audio(0);

    rest(100);
    // Reset the video timer (it has been running since we opened the mpeg).
    stream->timer = -1;
    while(stream->timer == -1);

    while(apeg_advance_stream(stream, 0) == APEG_OK)
    {
        if(keypressed())
            break;
        rest(10);
    }
    apeg_close_stream(stream);
    return APEG_OK;
}
