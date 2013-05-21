
#ifndef EARTH_H_INCLUDED
#define EARTH_H_INCLUDED

#include "includes.h"

typedef enum {Tunisia,Egypt,Japan,Malaysia,India} LocationName;
//defines a location is space.
typedef struct {
    float xRot;
    float yRot;
    float zRot;
    float xTran;
    float yTran;
    float zTran;
    LocationName name;
} Location;

//the location of the countries in space.
Location TUNISIA,EGYPT,JAPAN,MALAYSIA,INDIA;
//Images for the map of earth, and the stars of space.
IMAGE *world,*stars;
//define travel mode. INTERPOLATED is better.
typedef enum {LINEAR,INTERPOLATED} TravelMode;

//Travels from a country to another.
void DoEarth(Location start, Location end);
//Advances the position of the traveling.
//this function is called from DoEarth
Location Travel(Location start,Location end,float percentage,TravelMode t);

//A modified version of gluSphere to map small textures
void gluSphere2(GLUquadric *qobj, GLdouble radius, GLint slices, GLint stacks,GLdouble CoordScale);

//glu defines
#define CACHE_SIZE	240

#undef	PI
#define PI	      3.14159265358979323846
#define SIN sin
#define COS cos


struct GLUquadric {
    GLint	normals;
    GLboolean	textureCoords;
    GLint	orientation;
    GLint	drawStyle;
};


#endif // EARTH_H_INCLUDED
