#include "includes.h"

Point **SalahCollision;
Point **HaithamCollision;


int ProcessCollision(IMAGE ** pics1, int index1, Point **Data1,float x1,float y1,float w1,float h1,
                     IMAGE ** pics2, int index2, Point **Data2,float x2,float y2,float w2,float h2)
{
    int i=0,j=0;
    Point pt1,pt2,pt3,pt4;

    //testing for valid params
    if ((w1==0 && h1==0) || (w2==0 && h2==0)) return 0;

    if(w1==0 && h1!=0){
        w1=(h1/((float)pics1[index1]->h/(float)pics1[index1]->w))/AspectRatio;
    }
    if(w1!=0 && h1==0){
        h1=(w1/((float)pics1[index1]->w/(float)pics1[index1]->h))*AspectRatio;
    }
    if(w2==0 && h2!=0){
        w2=(h2/((float)pics2[index2]->h/(float)pics2[index2]->w))/AspectRatio;
    }
    if(w2!=0 && h2==0){
        h2=(w2/((float)pics2[index2]->w/(float)pics2[index2]->h))*AspectRatio;
    }

    //if there is data
    if (Data1[index1]!=NULL && Data2[index2]!=NULL)
    {
        for(i=0; Data1[index1][i+1].X!=-1; i++)
        {
            //Convert points1 from image coords to screen coords
            pt1.X=(Data1[index1][i].X/(float)pics1[index1]->w)*w1 + x1;
            pt1.Y=(Data1[index1][i].Y/(float)pics1[index1]->h)*h1 + y1;
            pt2.X=(Data1[index1][i+1].X/(float)pics1[index1]->w)*w1 + x1;
            pt2.Y=(Data1[index1][i+1].Y/(float)pics1[index1]->h)*h1 + y1;

            //TODO : test the last point and the first point.
            for(j=0; Data2[index2][j+1].X!=-1; j++)
            {
                //Convert points2 from image coords to screen coords
                pt3.X=(Data2[index2][j].X/(float)pics2[index2]->w)*w2 + x2;
                pt3.Y=(Data2[index2][j].Y/(float)pics2[index2]->h)*h2 + y2;
                pt4.X=(Data2[index2][j+1].X/(float)pics2[index2]->w)*w2 + x2;
                pt4.Y=(Data2[index2][j+1].Y/(float)pics2[index2]->h)*h2 + y2;

                if(Intersect(pt1,pt2,pt3,pt4))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}


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
/*
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
}*/

void LoadCollisionData()
{
    char Section[255],buffer[255],*data=NULL;
    int i,j,count;
    set_config_file("Resources/Collision.cfg");
    //Loading Salah Data
    sprintf(Section,"/Resources/Images/Salah/GamePlay");
    SalahCollision=calloc(SalahImageCount,sizeof(Point*));
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
    HaithamCollision=calloc(HaithamImageCount,sizeof(Point*));
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
    set_config_file("Resources/Setting.cfg");
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



