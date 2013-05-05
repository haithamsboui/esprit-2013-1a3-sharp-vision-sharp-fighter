#include "includes.h"

Point **SalahCollision;
Point **HaithamCollision;

int Intersect(Point pt1,Point pt2,Point pt3,Point pt4)
{
    float A1, A2, B1, B2, C1, C2, det;
    Point inter;
    A1 = pt2.Y - pt1.Y;
    B1 = pt1.X - pt2.X;
    C1 = A1 * pt1.X + B1 * pt1.Y;
    A2 = pt4.Y - pt3.Y;
    B2 = pt3.X - pt4.X;
    C2 = A2 * pt3.X + B2 * pt3.Y;
    det = A1 * B2 - A2 * B1;
    if(det != 0)
    {
        inter.X = (B2 * C1 - B1 * C2) / det;
        inter.Y = (A1 * C2 - A2 * C1) / det;
        if(Min(pt1.X, pt2.X) <= inter.X && Max(pt1.X, pt2.X) >= inter.X &&
                Min(pt1.Y, pt2.Y) <= inter.Y && Max(pt1.Y, pt2.Y) >= inter.Y &&
                Min(pt3.X, pt4.X) <= inter.X && Max(pt3.X, pt4.X) >= inter.X &&
                Min(pt3.Y, pt4.Y) <= inter.Y && Max(pt3.Y, pt4.Y) >= inter.Y)
        {
            return 1;
        }
    }
    return 0;
}

int Collision(Point Shape1[], int n1,Point Shape2[], int n2)
{
    int i,j;
    for(i=0; i<n1; i++)
    {
        for(j=0; j<n2; j++)
        {
            if(Intersect(Shape1[i],Shape1[(i+1)%n1],Shape2[j],Shape2[(j+1)%n2]))
            {
                return 1;
            }
        }
    }
    return 0;
}

void LoadCollisionData()
{
    char Section[255],buffer[255],*data=NULL;
    int i,j,count;
    set_config_file("Resources/Collision.cfg");
    //Loading Salah Data
    sprintf(Section,"/Resources/Images/Salah/GamePlay");
    SalahCollision=malloc(SalahImageCount*sizeof(Point*));
    for(i=0; i<SalahImageCount; i++)
    {
        sprintf(buffer,"%s/%d.png.Count",Section,i);
        count=get_config_int(Section,buffer,0);
        sprintf(buffer,"%s/%d.png.Data",Section,i);
        data=get_config_string(Section,buffer,NULL);

        if(count && data!=NULL)
        {
            SalahCollision[i]=malloc((count+1)*sizeof(Point));

            SalahCollision[i][0].X=atoi(strtok(data,","));
            SalahCollision[i][0].Y=atoi(strtok(NULL,","));
            for(j=1; j<count; j++)
            {
                SalahCollision[i][j].X=atoi(strtok(NULL,","));
                SalahCollision[i][j].Y=atoi(strtok(NULL,","));
            }
            SalahCollision[i][j].X=-1;
            SalahCollision[i][j].Y=-1;
        }
    }
    //Loading Haitham Data
    sprintf(Section,"/Resources/Images/Haitham/GamePlay");
    SalahCollision=malloc(HaithamImageCount*sizeof(Point*));
    for(i=0; i<HaithamImageCount; i++)
    {
        sprintf(buffer,"%s/%d.png.Count",Section,i);
        count=get_config_int(Section,buffer,0);
        sprintf(buffer,"%s/%d.png.Data",Section,i);
        data=get_config_string(Section,buffer,NULL);

        if(count && data!=NULL)
        {
            HaithamCollision[i]=malloc((count+1)*sizeof(Point));

            HaithamCollision[i][0].X=atoi(strtok(data,","));
            HaithamCollision[i][0].Y=atoi(strtok(NULL,","));
            for(j=1; j<count; j++)
            {
                HaithamCollision[i][j].X=atoi(strtok(NULL,","));
                HaithamCollision[i][j].Y=atoi(strtok(NULL,","));
            }
            HaithamCollision[i][j].X=-1;
            HaithamCollision[i][j].Y=-1;
        }
    }
}

void UnLoadCollisionData()
{
    int i;
    for(i=0; i<SalahImageCount; i++)
    {
        free(SalahCollision[i]);
    }
    free(SalahCollision);
    for(i=0; i<HaithamImageCount; i++)
    {
        free(HaithamCollision[i]);
    }
    free(HaithamCollision);
}
