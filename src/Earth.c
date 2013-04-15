#include "includes.h"

Location TUNISIA = {.xRot=-112.0f,.yRot=0.0f,.zRot=-9.5f,.xTran=0.0f,.yTran=-0.6f,.zTran=-0.6f,.name=Tunisia};
Location EGYPT = {.xRot=-121.0f,.yRot=0.0f,.zRot=-29.5f,.xTran=0.0f,.yTran=-0.6f,.zTran=-0.6f,.name=Egypt};
Location FRANCE = {.xRot=-100.0f,.yRot=0.0f,.zRot=-2.5f,.xTran=0.0f,.yTran=-0.6f,.zTran=-0.6f,.name=France};
Location NEWYORK = {.xRot=-100.0f,.yRot=0.0f,.zRot=75.5f,.xTran=0.0f,.yTran=-0.6f,.zTran=-0.8f,.name=NewYork};
Location JAPAN = {.xRot=-106.0f,.yRot=0.0f,.zRot=-138.0f,.xTran=0.0f,.yTran=-0.6f,.zTran=-0.8f,.name=Japan};
Location MALAYSIA = {.xRot=-87.0f,.yRot=0.0f,.zRot=-101.0f,.xTran=0.0f,.yTran=-0.0f,.zTran=-1.0f,.name=Malaysia};
//gluDeleteQuadric(quadratic);
GLUquadricObj* quadratic;
IMAGE *world,*stars;

void DoEarth(Location start, Location end)
{
    char text[100];
    Location Current;
    float perc=0.0f;


    if(world==NULL)
    {
        world=load_image("Resources/Images/Earth/world.png");
        if(world==NULL) return;
    }

    if(stars==NULL)
    {
        stars=load_image("Resources/Images/Earth/stars.png");
        if(stars==NULL) return;
    }


    glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW); //or GL_CW for clockwise front face
    glEnable(GL_CULL_FACE); //which you already have
    quadratic=gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);					// Create Smooth Normals
    gluQuadricTexture(quadratic, GL_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(float)SCREEN_W/(float)SCREEN_H, 0.000001, 10.0);
    glMatrixMode(GL_MODELVIEW);
    rest(500);
    while(perc<100)
    {
        Current=Travel(start,end,perc,INTERPOLATED);
        perc+=0.5f;
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glLoadIdentity();
        glTranslatef(Current.xTran,Current.yTran,Current.zTran);
        glRotatef(Current.xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(Current.yRot, 0.0f, 1.0f, 0.0f);
        glRotatef(Current.zRot, 0.0f, 0.0f, 1.0f);

        glCullFace(GL_FRONT);
        glBindTexture(GL_TEXTURE_2D, stars->ID);
        gluSphere2(quadratic,6.0f,20,20,8.0f);

        glCullFace(GL_BACK);
        glBindTexture(GL_TEXTURE_2D, world->ID);
        gluSphere(quadratic,0.7f,50,50);

        next_frame();
    }
    perc=0;
    switch(end.name){
        case Malaysia:
            sprintf(text,"Kuala Lumpur - Malaysia");
        break;
        case Japan:
            sprintf(text,"Tokyo - Japan");
        break;
        case Tunisia:
            sprintf(text,"Tunis - Tunisia");
        break;

    }
    while(perc<200)
    {
        perc+=1;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0,(float)SCREEN_W/(float)SCREEN_H, 0.000001, 10.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(Current.xTran,Current.yTran,Current.zTran);
        glRotatef(Current.xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(Current.yRot, 0.0f, 1.0f, 0.0f);
        glRotatef(Current.zRot, 0.0f, 0.0f, 1.0f);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glCullFace(GL_FRONT);
        glBindTexture(GL_TEXTURE_2D, stars->ID);
        gluSphere2(quadratic,6.0f,20,20,8.0f);

        glCullFace(GL_BACK);
        glBindTexture(GL_TEXTURE_2D, world->ID);
        gluSphere(quadratic,0.7f,50,50);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluOrtho2D(-1,1,-1,1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        draw_text(Arista,text,10,50,50,CENTER,perc);

        next_frame();
    }

    gluDeleteQuadric(quadratic);
    SetOpenGL2D();
}


Location Travel(Location start,Location end,float percentage,TravelMode t)
{
    Location l;
    float d = sqrtf(powf(end.zRot-start.zRot,2)+powf(end.xRot-start.xRot,2))/180;
    Pointf PercenPoints[]= {{.x=0.0f,.y=0.0f},{.x=25.0f,.y=12.5f},{.x=50.0f,.y=50.0f},{.x=75.0f,.y=87.5f},{.x=95.0f,.y=99.5f},{.x=100.0f,.y=100.0f}};
    Pointf zPoints[]= {{.x=0.0f,.y=start.zTran},{.x=50.0f,.y=-2.0f*d-0.6f},{.x=100.0f,.y=end.zTran}};

    percentage= percentage>0.0f ? percentage : 0.0f;
    percentage= percentage<100.0f ? percentage : 100.0f;
    switch(t)
    {
    case LINEAR:
        l.xRot=LinearFunc(start.xRot,end.xRot,percentage);
        l.yRot=LinearFunc(start.yRot,end.yRot,percentage);
        l.zRot=LinearFunc(start.zRot,end.zRot,percentage);
        l.xTran=LinearFunc(start.xTran,end.xTran,percentage);
        l.yTran=LinearFunc(start.yTran,end.yTran,percentage);
        l.zTran=LinearFunc(start.zTran,end.zTran,percentage);
        break;
    case INTERPOLATED:
        percentage=LaGrange(PercenPoints,sizeof(PercenPoints)/sizeof(Pointf),percentage);
        l.xRot=LinearFunc(start.xRot,end.xRot,percentage);
        l.yRot=LinearFunc(start.yRot,end.yRot,percentage);
        l.zRot=LinearFunc(start.zRot,end.zRot,percentage);
        l.xTran=LinearFunc(start.xTran,end.xTran,percentage);
        l.yTran=LinearFunc(start.yTran,end.yTran,percentage);
        l.zTran=LaGrange(zPoints,3,percentage); //LinearFunc(start.zTran,end.zTran,percentage);
        break;
    }

    return l;
}

void gluSphere2(GLUquadric *qobj, GLdouble radius, GLint slices, GLint stacks,GLdouble CoordScale)
{
    GLint i,j;
    GLfloat sinCache1a[CACHE_SIZE];
    GLfloat cosCache1a[CACHE_SIZE];
    GLfloat sinCache2a[CACHE_SIZE];
    GLfloat cosCache2a[CACHE_SIZE];
    GLfloat sinCache3a[CACHE_SIZE];
    GLfloat cosCache3a[CACHE_SIZE];
    GLfloat sinCache1b[CACHE_SIZE];
    GLfloat cosCache1b[CACHE_SIZE];
    GLfloat sinCache2b[CACHE_SIZE];
    GLfloat cosCache2b[CACHE_SIZE];
    GLfloat sinCache3b[CACHE_SIZE];
    GLfloat cosCache3b[CACHE_SIZE];
    GLfloat angle;
    GLfloat zLow, zHigh;
    GLfloat sintemp1 = 0.0, sintemp2 = 0.0, sintemp3 = 0.0, sintemp4 = 0.0;
    GLfloat costemp1 = 0.0, costemp2 = 0.0, costemp3 = 0.0, costemp4 = 0.0;
    GLboolean needCache2, needCache3;
    GLint start, finish;

    if (slices >= CACHE_SIZE) slices = CACHE_SIZE-1;
    if (stacks >= CACHE_SIZE) stacks = CACHE_SIZE-1;
    if (slices < 2 || stacks < 1 || radius < 0.0)
    {

        return;
    }

    /* Cache is the vertex locations cache */
    /* Cache2 is the various normals at the vertices themselves */
    /* Cache3 is the various normals for the faces */
    needCache2 = needCache3 = GL_FALSE;

    if (qobj->normals == GLU_SMOOTH)
    {
        needCache2 = GL_TRUE;
    }

    if (qobj->normals == GLU_FLAT)
    {
        if (qobj->drawStyle != GLU_POINT)
        {
            needCache3 = GL_TRUE;
        }
        if (qobj->drawStyle == GLU_LINE)
        {
            needCache2 = GL_TRUE;
        }
    }

    for (i = 0; i < slices; i++)
    {
        angle = 2 * PI * i / slices;
        sinCache1a[i] = SIN(angle);
        cosCache1a[i] = COS(angle);
        if (needCache2)
        {
            sinCache2a[i] = sinCache1a[i];
            cosCache2a[i] = cosCache1a[i];
        }
    }

    for (j = 0; j <= stacks; j++)
    {
        angle = PI * j / stacks;
        if (needCache2)
        {
            if (qobj->orientation == GLU_OUTSIDE)
            {
                sinCache2b[j] = SIN(angle);
                cosCache2b[j] = COS(angle);
            }
            else
            {
                sinCache2b[j] = -SIN(angle);
                cosCache2b[j] = -COS(angle);
            }
        }
        sinCache1b[j] = radius * SIN(angle);
        cosCache1b[j] = radius * COS(angle);
    }
    /* Make sure it comes to a point */
    sinCache1b[0] = 0;
    sinCache1b[stacks] = 0;

    if (needCache3)
    {
        for (i = 0; i < slices; i++)
        {
            angle = 2 * PI * (i-0.5) / slices;
            sinCache3a[i] = SIN(angle);
            cosCache3a[i] = COS(angle);
        }
        for (j = 0; j <= stacks; j++)
        {
            angle = PI * (j - 0.5) / stacks;
            if (qobj->orientation == GLU_OUTSIDE)
            {
                sinCache3b[j] = SIN(angle);
                cosCache3b[j] = COS(angle);
            }
            else
            {
                sinCache3b[j] = -SIN(angle);
                cosCache3b[j] = -COS(angle);
            }
        }
    }

    sinCache1a[slices] = sinCache1a[0];
    cosCache1a[slices] = cosCache1a[0];
    if (needCache2)
    {
        sinCache2a[slices] = sinCache2a[0];
        cosCache2a[slices] = cosCache2a[0];
    }
    if (needCache3)
    {
        sinCache3a[slices] = sinCache3a[0];
        cosCache3a[slices] = cosCache3a[0];
    }

    switch (qobj->drawStyle)
    {
    case GLU_FILL:
        /* Do ends of sphere as TRIANGLE_FAN's (if not texturing)
        ** We don't do it when texturing because we need to respecify the
        ** texture coordinates of the apex for every adjacent vertex (because
        ** it isn't a constant for that point)
        */
        if (!(qobj->textureCoords))
        {
            start = 1;
            finish = stacks - 1;

            /* Low end first (j == 0 iteration) */
            sintemp2 = sinCache1b[1];
            zHigh = cosCache1b[1];
            switch(qobj->normals)
            {
            case GLU_FLAT:
                sintemp3 = sinCache3b[1];
                costemp3 = cosCache3b[1];
                break;
            case GLU_SMOOTH:
                sintemp3 = sinCache2b[1];
                costemp3 = cosCache2b[1];
                glNormal3f(sinCache2a[0] * sinCache2b[0],
                           cosCache2a[0] * sinCache2b[0],
                           cosCache2b[0]);
                break;
            default:
                break;
            }
            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0, 0.0, radius);
            if (qobj->orientation == GLU_OUTSIDE)
            {
                for (i = slices; i >= 0; i--)
                {
                    switch(qobj->normals)
                    {
                    case GLU_SMOOTH:
                        glNormal3f(sinCache2a[i] * sintemp3,
                                   cosCache2a[i] * sintemp3,
                                   costemp3);
                        break;
                    case GLU_FLAT:
                        if (i != slices)
                        {
                            glNormal3f(sinCache3a[i+1] * sintemp3,
                                       cosCache3a[i+1] * sintemp3,
                                       costemp3);
                        }
                        break;
                    case GLU_NONE:
                    default:
                        break;
                    }
                    glVertex3f(sintemp2 * sinCache1a[i],
                               sintemp2 * cosCache1a[i], zHigh);
                }
            }
            else
            {
                for (i = 0; i <= slices; i++)
                {
                    switch(qobj->normals)
                    {
                    case GLU_SMOOTH:
                        glNormal3f(sinCache2a[i] * sintemp3,
                                   cosCache2a[i] * sintemp3,
                                   costemp3);
                        break;
                    case GLU_FLAT:
                        glNormal3f(sinCache3a[i] * sintemp3,
                                   cosCache3a[i] * sintemp3,
                                   costemp3);
                        break;
                    case GLU_NONE:
                    default:
                        break;
                    }
                    glVertex3f(sintemp2 * sinCache1a[i],
                               sintemp2 * cosCache1a[i], zHigh);
                }
            }
            glEnd();

            /* High end next (j == stacks-1 iteration) */
            sintemp2 = sinCache1b[stacks-1];
            zHigh = cosCache1b[stacks-1];
            switch(qobj->normals)
            {
            case GLU_FLAT:
                sintemp3 = sinCache3b[stacks];
                costemp3 = cosCache3b[stacks];
                break;
            case GLU_SMOOTH:
                sintemp3 = sinCache2b[stacks-1];
                costemp3 = cosCache2b[stacks-1];
                glNormal3f(sinCache2a[stacks] * sinCache2b[stacks],
                           cosCache2a[stacks] * sinCache2b[stacks],
                           cosCache2b[stacks]);
                break;
            default:
                break;
            }
            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0, 0.0, -radius);
            if (qobj->orientation == GLU_OUTSIDE)
            {
                for (i = 0; i <= slices; i++)
                {
                    switch(qobj->normals)
                    {
                    case GLU_SMOOTH:
                        glNormal3f(sinCache2a[i] * sintemp3,
                                   cosCache2a[i] * sintemp3,
                                   costemp3);
                        break;
                    case GLU_FLAT:
                        glNormal3f(sinCache3a[i] * sintemp3,
                                   cosCache3a[i] * sintemp3,
                                   costemp3);
                        break;
                    case GLU_NONE:
                    default:
                        break;
                    }
                    glVertex3f(sintemp2 * sinCache1a[i],
                               sintemp2 * cosCache1a[i], zHigh);
                }
            }
            else
            {
                for (i = slices; i >= 0; i--)
                {
                    switch(qobj->normals)
                    {
                    case GLU_SMOOTH:
                        glNormal3f(sinCache2a[i] * sintemp3,
                                   cosCache2a[i] * sintemp3,
                                   costemp3);
                        break;
                    case GLU_FLAT:
                        if (i != slices)
                        {
                            glNormal3f(sinCache3a[i+1] * sintemp3,
                                       cosCache3a[i+1] * sintemp3,
                                       costemp3);
                        }
                        break;
                    case GLU_NONE:
                    default:
                        break;
                    }
                    glVertex3f(sintemp2 * sinCache1a[i],
                               sintemp2 * cosCache1a[i], zHigh);
                }
            }
            glEnd();
        }
        else
        {
            start = 0;
            finish = stacks;
        }
        for (j = start; j < finish; j++)
        {
            zLow = cosCache1b[j];
            zHigh = cosCache1b[j+1];
            sintemp1 = sinCache1b[j];
            sintemp2 = sinCache1b[j+1];
            switch(qobj->normals)
            {
            case GLU_FLAT:
                sintemp4 = sinCache3b[j+1];
                costemp4 = cosCache3b[j+1];
                break;
            case GLU_SMOOTH:
                if (qobj->orientation == GLU_OUTSIDE)
                {
                    sintemp3 = sinCache2b[j+1];
                    costemp3 = cosCache2b[j+1];
                    sintemp4 = sinCache2b[j];
                    costemp4 = cosCache2b[j];
                }
                else
                {
                    sintemp3 = sinCache2b[j];
                    costemp3 = cosCache2b[j];
                    sintemp4 = sinCache2b[j+1];
                    costemp4 = cosCache2b[j+1];
                }
                break;
            default:
                break;
            }

            glBegin(GL_QUAD_STRIP);
            for (i = 0; i <= slices; i++)
            {
                switch(qobj->normals)
                {
                case GLU_SMOOTH:
                    glNormal3f(sinCache2a[i] * sintemp3,
                               cosCache2a[i] * sintemp3,
                               costemp3);
                    break;
                case GLU_FLAT:
                case GLU_NONE:
                default:
                    break;
                }
                if (qobj->orientation == GLU_OUTSIDE)
                {
                    if (qobj->textureCoords)
                    {
                        glTexCoord2f((1 - (float) i / slices)*CoordScale,
                                     (1 - (float) (j+1) / stacks)*CoordScale);
                    }
                    glVertex3f(sintemp2 * sinCache1a[i],
                               sintemp2 * cosCache1a[i], zHigh);
                }
                else
                {
                    if (qobj->textureCoords)
                    {
                        glTexCoord2f((1 - (float) i / slices)*CoordScale,
                                     (1 - (float) j / stacks)*CoordScale);
                    }
                    glVertex3f(sintemp1 * sinCache1a[i],
                               sintemp1 * cosCache1a[i], zLow);
                }
                switch(qobj->normals)
                {
                case GLU_SMOOTH:
                    glNormal3f(sinCache2a[i] * sintemp4,
                               cosCache2a[i] * sintemp4,
                               costemp4);
                    break;
                case GLU_FLAT:
                    glNormal3f(sinCache3a[i] * sintemp4,
                               cosCache3a[i] * sintemp4,
                               costemp4);
                    break;
                case GLU_NONE:
                default:
                    break;
                }
                if (qobj->orientation == GLU_OUTSIDE)
                {
                    if (qobj->textureCoords)
                    {
                        glTexCoord2f((1 - (float) i / slices)*CoordScale,
                                     (1 - (float) j / stacks)*CoordScale);
                    }
                    glVertex3f(sintemp1 * sinCache1a[i],
                               sintemp1 * cosCache1a[i], zLow);
                }
                else
                {
                    if (qobj->textureCoords)
                    {
                        glTexCoord2f((1 - (float) i / slices)*CoordScale,
                                     (1 - (float) (j+1) / stacks)*CoordScale);
                    }
                    glVertex3f(sintemp2 * sinCache1a[i],
                               sintemp2 * cosCache1a[i], zHigh);
                }
            }
            glEnd();
        }
        break;
    case GLU_POINT:
        glBegin(GL_POINTS);
        for (j = 0; j <= stacks; j++)
        {
            sintemp1 = sinCache1b[j];
            costemp1 = cosCache1b[j];
            switch(qobj->normals)
            {
            case GLU_FLAT:
            case GLU_SMOOTH:
                sintemp2 = sinCache2b[j];
                costemp2 = cosCache2b[j];
                break;
            default:
                break;
            }
            for (i = 0; i < slices; i++)
            {
                switch(qobj->normals)
                {
                case GLU_FLAT:
                case GLU_SMOOTH:
                    glNormal3f(sinCache2a[i] * sintemp2,
                               cosCache2a[i] * sintemp2,
                               costemp2);
                    break;
                case GLU_NONE:
                default:
                    break;
                }

                zLow = j * radius / stacks;

                if (qobj->textureCoords)
                {
                    glTexCoord2f((1 - (float) i / slices)*CoordScale,
                                 (1 - (float) j / stacks)*CoordScale);
                }
                glVertex3f(sintemp1 * sinCache1a[i],
                           sintemp1 * cosCache1a[i], costemp1);
            }
        }
        glEnd();
        break;
    case GLU_LINE:
    case GLU_SILHOUETTE:
        for (j = 1; j < stacks; j++)
        {
            sintemp1 = sinCache1b[j];
            costemp1 = cosCache1b[j];
            switch(qobj->normals)
            {
            case GLU_FLAT:
            case GLU_SMOOTH:
                sintemp2 = sinCache2b[j];
                costemp2 = cosCache2b[j];
                break;
            default:
                break;
            }

            glBegin(GL_LINE_STRIP);
            for (i = 0; i <= slices; i++)
            {
                switch(qobj->normals)
                {
                case GLU_FLAT:
                    glNormal3f(sinCache3a[i] * sintemp2,
                               cosCache3a[i] * sintemp2,
                               costemp2);
                    break;
                case GLU_SMOOTH:
                    glNormal3f(sinCache2a[i] * sintemp2,
                               cosCache2a[i] * sintemp2,
                               costemp2);
                    break;
                case GLU_NONE:
                default:
                    break;
                }
                if (qobj->textureCoords)
                {
                    glTexCoord2f((1 - (float) i / slices)*CoordScale,
                                 (1 - (float) j / stacks)*CoordScale);
                }
                glVertex3f(sintemp1 * sinCache1a[i],
                           sintemp1 * cosCache1a[i], costemp1);
            }
            glEnd();
        }
        for (i = 0; i < slices; i++)
        {
            sintemp1 = sinCache1a[i];
            costemp1 = cosCache1a[i];
            switch(qobj->normals)
            {
            case GLU_FLAT:
            case GLU_SMOOTH:
                sintemp2 = sinCache2a[i];
                costemp2 = cosCache2a[i];
                break;
            default:
                break;
            }

            glBegin(GL_LINE_STRIP);
            for (j = 0; j <= stacks; j++)
            {
                switch(qobj->normals)
                {
                case GLU_FLAT:
                    glNormal3f(sintemp2 * sinCache3b[j],
                               costemp2 * sinCache3b[j],
                               cosCache3b[j]);
                    break;
                case GLU_SMOOTH:
                    glNormal3f(sintemp2 * sinCache2b[j],
                               costemp2 * sinCache2b[j],
                               cosCache2b[j]);
                    break;
                case GLU_NONE:
                default:
                    break;
                }

                if (qobj->textureCoords)
                {
                    glTexCoord2f((1 - (float) i / slices)*CoordScale,
                                 (1 - (float) j / stacks)*CoordScale);
                }
                glVertex3f(sintemp1 * sinCache1b[j],
                           costemp1 * sinCache1b[j], cosCache1b[j]);
            }
            glEnd();
        }
        break;
    default:
        break;
    }
}

