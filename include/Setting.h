#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

int Music_volume; // 0-255
int Effect_volume; // 0-255

int Fullscreen;
int Width;
int Height;
int depth;

void LoadSettings();
GFX_MODE_LIST GetResolution();
#endif // SETTING_H_INCLUDED
