#include <iostream>
#include<cv.h>
#include<highgui.h>
#include<cv.h>
#define black 0
//#define white(c) 255
#define forr(i,N) for(int i=0;i<N;i++)
#define SET(x,val) memset(x,val,sizeof val);
#define al 212
using namespace std;
using namespace cv;

int rows,cols,ch;int visit[1111][1111];
int dx[4]={1,-1,0,0};int dy[4]={0,0,-1,1};
//int color[1111][1111];
Mat img,newimg,newimg2;
Vec3b color;Vec3b white;
Vec3b blacky;//int al=252;

int check(int x,int y)
{
    if(x>=rows || x<0 || y>=cols || y<0 ) {return 0;}
    return 1;
}

int same(int x1,int y1,int x2,int y2)
{
    Vec3b temp1=img.at<Vec3b>(x1,y1);Vec3b temp2=img.at<Vec3b>(x2,y2);
    if(temp1.val[0]!=temp2.val[0]) return 0;
    if(temp1.val[1]!=temp2.val[1]) return 0;
    if(temp1.val[2]!=temp2.val[2]) return 0;
    return 1;
}

int same2(int x1,int y1,int x2,int y2)
{
    Vec3b temp1=newimg.at<Vec3b>(x1,y1);Vec3b temp2=newimg.at<Vec3b>(x2,y2);
    if(temp2.val[0]!=black) return 1;
    if(temp2.val[1]!=black) return 1;
    if(temp2.val[2]!=black) return 1;
    return 0;
}


int bl(int x,int y)
{
  Vec3b temp=img.at<Vec3b>(x,y);
 if(temp.val[0]>al || temp.val[1]>al || temp.val[2]>al)  {return 0;}
 return 1;
}

int dfs(int x,int y)
{
    if( bl(x,y)) { newimg.at<Vec3b>(x,y)[0]=black;newimg.at<Vec3b>(x,y)[1]=black;
    newimg.at<Vec3b>(x,y)[2]=black;;visit[x][y]=1;return 0;}
    visit[x][y]=1;
    forr(k,4)
    {
        int newx=x+dx[k];int newy=y+dy[k];
        if(!visit[newx][newy] && same(x,y,newx,newy) && check(newx,newy))
        {
            newimg.at<Vec3b>(newx,newy)=color;
            dfs(newx,newy);
        }
    }
}




int dfs2(int x,int y)
{
   // if( bl(x,y)) { newimg.at<Vec3b>(x,y)[0]=black;newimg.at<Vec3b>(x,y)[1]=black;
 //   newimg.at<Vec3b>(x,y)[2]=black;color[x][y]=-1;visit[x][y]=1;return 0;}
    //if( ) {return 0;}
    visit[x][y]=1;
    forr(k,4)
    {
        int newx=x+dx[k];int newy=y+dy[k];
        if(visit[newx][newy]==0 && same2(x,y,newx,newy) && check(newx,newy))
        {
            newimg2.at<Vec3b>(newx,newy)=color;
            dfs2(newx,newy);
        }
    }
}
void MyFilledCircle( Mat img, Point center )
{
 int thickness = -1;
 int lineType = 8;

 circle( img,
         center,
         20,
         Scalar( 0, 0, 255 ),
         thickness,
         lineType );
}
int alpha;
int mycall()
{
      blacky.val[0]=0;blacky.val[1]=0;blacky.val[2]=0;
     white.val[0]=255;white.val[1]=255;white.val[2]=255;
    SET(visit,0);
    //cout << "Hello world!" << endl;
    img=imread("stuff.jpg",1);
    printf(" YO\n ");
    imshow(" Connected Componentffssfss ",img);
    //al=252;
    //al=alpha;
//    imshow();
   rows=img.rows;cols=img.cols;ch=img.channels();
 //   threshold(img);
   // while(waitKey()!=27);
    int tot=1,cmp=0;
    newimg=Mat::zeros(img.size(),img.type());
    newimg2=Mat::zeros(img.size(),img.type());
    printf("%d %d %d \n",rows,cols,ch);
    color=white;cmp=0;
    forr(x,rows)
    {
        forr(y,cols)
        {
            if( bl(x,y)) { newimg.at<Vec3b>(x,y)=blacky;visit[x][y]=1;continue;}
            if(visit[x][y]) {continue;}
            visit[x][y]=1;
           // color[x][y]=tot++;;
            newimg.at<Vec3b>(x,y)=color;
            dfs(x,y);
            cmp++;
        }
    }
    printf(" Initially %d\n ",cmp);
    imshow(" Threshed ",newimg);
    //while(waitKey()!=27);
    //SET(visit,0)
    cmp=0;int flag=0;
    printf(" Total Components are %d\n",cmp);
    //imshow(" efe ",newimg);
    forr(i,rows)
    {
        forr(j,cols)
        {
            visit[i][j]=0;
        }
    }
    Mat newimg3=newimg2;char chh;
     double xx=0,yy=0,to=0;
     forr(x,rows)
     {
        forr(y,cols)
        {
          if(newimg.at<Vec3b>(x,y)==white)
           {
             //  MyFilledCircle(newimg3,Point(rows-x-1+100,cols-y-1-10));
               //imshow(" here ",newimg3);//while(waitKey()!=27);
//               getc();
               //cin>>chh;
               xx=xx+(x);yy=yy+y;to++;
           }
        }
     }
    printf("total %llf ",to);
    forr(x,rows)
    {
        forr(y,cols)
        {
  //          if( bl(x,y)) { newimg.at<Vec3b>(x,y)[0]=black;newimg.at<Vec3b>(x,y)[1]=black;
//            newimg.at<Vec3b>(x,y)[2]=black;color[x][y]=-1;visit[x][y]=1;continue;}
            if(newimg.at<Vec3b>(x,y)==blacky){continue;}
            tot++;
            //flag=1;
            if(visit[x][y]==1) {continue;}
           // if(flag==0){ printf(" YEs");}
            visit[x][y]=1;
            color.val[0]=100+rand()%155;color.val[1]=100+rand()%155;
            color.val[2]=100+rand()%155;
            newimg2.at<Vec3b>(x,y)=color;
            dfs2(x,y);
            cmp++;
        }
    }
    printf(" Tot %d ",tot);
    printf(" Total Components are %d",cmp);
    xx=xx/(to);yy=yy/(to);
    MyFilledCircle(newimg2,Point(yy,xx));
    imshow(" Finally ",newimg2);
    //imshow(" in the end ",newimg3);

}

int main()
{
    //alpha=50;
    //Mat newimg3;
   //Mat newimg3=imread("stuff.jpg",1);
   // namedWindow("hello");
   ////MyFilledCircle(newimg3,Point(0,100));
   //imshow("Window ",newimg3);
   //MyFilledCircle(newimg3,Point(col));
    mycall();
    //namedWindow("window",0);
    //createTrackbar(" Threshold ", "window",&al,256,mycall);
    while(waitKey()!=27);
    return 0;
}
