#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
HMENU hmenu;
HMENU bmenu;
HWND g_hWnd;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;
    /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_HAND);/**mouse look*/
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;
    /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOWFRAME ;/**window color*/
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               600,                 /* The programs width */
               500,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL/* No Window Creation data */
           );

    /* Make the window visible on the screen */
    //Use it in clean screen
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
#include <cmath>
# include <iostream>
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <sstream>

void read(vector<int> &arr,string points)
{
    stringstream ss(points);/**Read the points from the file*/

    for (int i; ss >> i;)/**read the points and store it in vector and ignore the ',' char*/
    {
        arr.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
}

void prev(HDC hdc,vector<int> numbers,COLORREF c)
{
    for(int i = 0; i<numbers.size(); i+=2) /**every two points we set the pixel that has been stored in the sort vector*/
    {
        SetPixel(hdc,numbers[i],numbers[i+1],c);/**i=0,i=1 setpixel(0,1) // i=2,i=3 setpixel(2,3) and so on     */
    }
}

vector<int> savedPoints;
void save(int x,int y)
{
    savedPoints.push_back(x);
    savedPoints.push_back(y);
}

void SaveInFile()
{
    ofstream file;
    file.open("save.txt");/**open the file and start to storing in it */
    for(int i = 0; i<savedPoints.size(); i+=2)
    /**say x=10,y=20 the set point of a line (i=0 store 10) ',' (i=1 store 20) ','
    (i+=2)
    i=2 save another point 2,3 then i=4 and so on
     */
        file << savedPoints[i] << "," << savedPoints[i+1] << ",";

    file.close();
}

void drawPoint(HDC hdc,int xc,int yc,int x,int y,COLORREF c)
{
    save(xc+x,yc+y);
    save(xc-x,yc+y);
    save(xc-x,yc-y);
    save(xc+x,yc-y);

    save(xc+y,yc+x);
    save(xc-y,yc+x);
    save(xc-y,yc-x);
    save(xc+y,yc-x);

    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-x,yc-y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc+y,yc+x,c);
    SetPixel(hdc,xc-y,yc+x,c);
    SetPixel(hdc,xc-y,yc-x,c);
    SetPixel(hdc,xc+y,yc-x,c);
}
void Draw4Points(HDC hdc, int xc,int yc,int x,int y,COLORREF c)
{
    save(xc+x,yc+y);
    save(xc-x,yc+y);
    save(xc-x,yc-y);
    save(xc+x,yc-y);

    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-x,yc-y,c);
}
int Round(double x)
{
    return (int)(0.5+x);
}

/*LINES*/
void parametric(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C)
{
  /**
  x=x1+t*(x2-x1)
  y=y1+t*(y2-y1)
  t(0,1)
  say t=0.0001
  */
    int dx=x2-x1;
    int dy=y2-y1;
    double dt=1.0 / max(dx,dy);
    for(double t=0; t<1; t+=dt)
    {
        double x=x1+t*dx;
        double y=y1+t*dy;
        SetPixel(hdc,Round(x),Round(y),C);
        save(Round(x),Round(y));
    }
}

void DDA(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C)
{
    /**y=m*x+c
    y'=m*(x+1)+c
    y'=mx+m+c
    y'=y+m

    m=slope=dx/dy
    */
    int dx=x2-x1;
    int dy=y2-y1;
    if(abs(dx)>abs(dy))
    {

        if(x2<x1)
        {
            swap(x1,x2);
            swap(y1,y2);

            }
            double m=dy/dx;
            int x=x1;
            double y=y1;
            SetPixel(hdc,x,y,C);
            save(x,y);
            while(x2>x)
            {
                x++;
                y+=m;

                SetPixel(hdc,x,y,C);
                save(x,y);
            }
        }

    else
    {

        if(y2<y1)
        {
            swap(x1,x2);
            swap(y1,y2);
            }
            double m=(double)dx/dy;
            double x=x1;
            int y=y1;
            SetPixel(hdc,x,y,C);
            save(x,y);
            while(y2>y)
            {
                y++;
                x+=m;

                SetPixel(hdc,x,y,C);
                save(x,y);
            }
        }
    }

//doctor lecture code
void DDALine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
int dx=xe-xs;
int dy=ye-ys;
SetPixel(hdc,xs,ys,color);
save(xs,ys);
if(abs(dx)>=abs(dy))
{
int x=xs,xinc= dx>0?1:-1;
double y=ys,yinc=(double)dy/dx*xinc;
while(x!=xe)
{
x+=xinc;
y+=yinc;
SetPixel(hdc,x,round(y),color);
save(x,y);
}
}
else
{
int y=ys,yinc= dy>0?1:-1;
double x=xs,xinc=(double)dx/dy*yinc;
while(y!=ye)
{
x+=xinc;
y+=yinc;
SetPixel(hdc,round(x),y,color);
save(x,y);
}
}
}

void midpoint(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C)
{
    /**
    setpixel (x,y)

    dinitial 2*(x+1,y+0.5)=dx-2dy

    d>0 above the line
    dinitial+=-2dy

    d<0 under the line
    dinitial+=2dx-2dy
    */
    int x=x1;
    int y=y1;
    SetPixel(hdc,x,y,C);
    int dx=x2-x1;
    int dy=y2-y1;
    if(abs(dx)>=abs(dy))
    {
        int d=dx-2*dy;
        int d1=2*dx-2*dy;
        int d2=-2*dy;

        while(x<x2)
        {
            if(d>0)
            {
                d+=d2;
                x++;
            }
            else
            {
                d+=d1;
                x++;
                y++;
            }
            SetPixel(hdc,x,y,C);
            save(x,y);
        }

    }
    else
    {
        int d=2*dx-dy;
        int d1=2*dx-2*dy;
        int d2=2*dx;
        while(y<y2)
        {
            int x=x1;
            int y=y1;
            if(d>0)
            {
                d+=d1;
                y++;
            }
            else
            {
                d+=d2;
                y++;
                x++;
            }
            SetPixel(hdc,x,y,C);
            save(x,y);
        }
    }
}

/*LINES*/
/*CIRCLES */
void DirectPolar(HDC hdc,int xc,int yc,int r,COLORREF C)
{
    /**
    x=xc+rcostheta
    y=yc+rsintheta

    theta[0,2*pi]
    say theta=0.0001

    dtheta=1/r

    r=radius
    */
    double dtheta=1.0 / r;
    for(double theta=0; theta<6.28; theta+=dtheta)
    {
        double x=Round(xc+r*cos(theta));
        double y=Round(yc+r*sin(theta));
        SetPixel(hdc,x,y,C);
        save(x,y);
    }

}

void polar(HDC hdc,int xc,int yc,int r,COLORREF C)
{
    /**
    x=r(cos(theta))
    y=r(sin(theta))
    x'=r(cos(theta+dtheta))
    y'=r(sin(theta+dtheta))

    x'=xcos(dt)-ysin(dt)-->1
    y'=xsin(dt)+ycos(dt)-->2
    */
    double dtheta=1.0 / r;
    double c=cos(dtheta);
    double s=sin(dtheta);
    double x=r;
    double y=0;
    drawPoint(hdc,xc,yc,Round(x),Round(y),C);//first 8 point
    while(x>y)
    {
        x=x*c-y*s;
        y=x*s+y*c;
        drawPoint(hdc,xc,yc,Round(x),Round(y),C);
    }
}

void midpointCircle(HDC hdc,int xc,int yc,int r,COLORREF C)
{
    /**
    circleEqu=x^2+y^2-r^2
    dintial(x+1,y-0.5)=(5/4)-r == 1-r
    d1(x+2,y-0.5)=2x+3  if(d<0) inside circle x++ y=constant
    d2(x+2,y-1.5)=2(x-y)+5 if(d>0) outside circle  x++ y--
    */
    double y=r,x=0,d=1-r;
    drawPoint(hdc,xc,yc,Round(x),Round(y),C);
    while(x<=y)
    {
        if(d<0)
        {
            d+=2*x+3;
            x++;
        }
        else
        {
            d+=2*(x-y)+5;
            x++;
            y--;
        }
        drawPoint(hdc,xc,yc,Round(x),Round(y),C);
    }
}


void modifiedMidpoint(HDC hdc,int xc,int yc,int r,COLORREF C)
{
    /**
    second order difference
    x=0,y=r
    d1=2x+3
    d2=2(x-y)+5
    d1'=2(0)+3=3 -->1
    d2'=2(0-r)+5=5-2r -->2
    (d<0):
    change in d1=2(x+1)+3-(2x+3)=2 -->3
    (d>0):
    change in d2=2(x+1-y+1)+5-2(x-y)+5=4 -->4

    */
    int x=0,y=r;
    int d=1-r;
    int d1=3;
    int d2=5-2*r;
    while(x<=y)
    {
        if(d<0)
        {
            d+=d1;
            d2+=2;
            d1+=2;
            x++;
        }
        else
        {
            d+=d2;
            d2+=4;
            y--;
            d1+=2;
            x++;
        }
        drawPoint(hdc,xc,yc,Round(x),Round(y),C);
    }
}
/*CIRCLES*/
/*filling*/


struct Point
{
    int x,y;
    Point(int x,int y):x(x),y(y)
    {
    }
};
void MyFloodFill(HDC hdc,int x,int y, COLORREF BC,COLORREF FC,int num)
{
    stack <Point> st;//last in first out
    st.push(Point(x,y));
    while(!st.empty())
    {
        Point p=st.top();
        st.pop();
        COLORREF c= GetPixel(hdc, p.x,p.y );
        if (c==BC ||c==FC)
        {
            continue;
        }


        SetPixel(hdc,p.x,p.y,FC);
        save(p.x,p.y);
        if(num==1)
        {
            st.push(Point(p.x+1,p.y));
            st.push(Point(p.x,p.y-1));
        }
        if(num==2)
        {
            st.push(Point(p.x-1,p.y));
            st.push(Point(p.x,p.y-1));
        }
        if(num==3)
        {
            st.push(Point(p.x-1,p.y));
            st.push(Point(p.x,p.y+1));
        }
        if(num==4)
        {
            st.push(Point(p.x+1,p.y));
            st.push(Point(p.x,p.y+1));
        }
        if(num==5)
        {
            st.push(Point(p.x+1,p.y));
            st.push(Point(p.x-1,p.y));
            st.push(Point(p.x,p.y+1));
            st.push(Point(p.x,p.y-1));
        }
    }

}
/*Ellipse*/
void Ellipse(HDC hdc,int xc,int yc,int A,int B,COLORREF c)
{
    int x=0;
    int y=B;
    int d=(B*B)-((A*A)*(B+0.25));
    int d1=2*((B*B)*x)+3*(B*B);
    int d2=(B*B)*(2*x+3)+2*(A*A)*(1-y);
    Draw4Points(hdc,xc,yc,x,y,c);
    while (x*(B*B)<y*(A*A))
    {
        if (d<0)
        {
            d+=d1;
        }
        else if(d>0)
        {
            d+=d2;
            y--;
        }
        x++;
        Draw4Points(hdc,xc,yc,x,y,c);
    }
}

void DrawEllipsePolar(HDC hdc,int xc,int yc,int A,int B,COLORREF z)
{
    double dtheta=1.0/A;
    for(double theta=0.0; theta<6.28; theta+=dtheta)
    {
        double x=xc+B*cos(theta);
        double y=yc+A*sin(theta);
        SetPixel(hdc,Round(x),Round(y),z);
        save(Round(x),Round(y));
    }
}

void clearScreen()
{
#ifdef WINDOWS
    system("cls");
#else
    system("cls");
#endif
}


union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};


OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y<ytop)
        out.top=1;
    else if(y>ybottom)
        out.bottom=1;
    return out;
}


void VIntersect(double xs,double ys,double xe,double ye,int x,double *xi,double *yi)
{
    *xi=x;
    *yi=ys+(x-xs)*(ye-ys)/(xe-xs);
}
void HIntersect(double xs,double ys,double xe,double ye,int y,double *xi,double *yi)
{
    *yi=y;
    *xi=xs+(y-ys)*(xe-xs)/(ye-ys);
}


void CohenSuth(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom)
{
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out1.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {
        MoveToEx(hdc,Round(x1),Round(y1),NULL);
        LineTo(hdc,Round(x2),Round(y2));
    }
}

void PointClipping(HDC hdc,int x,int y,int xleft,int ytop,int xright,int ybottom,COLORREF color)
{
    if(x>=xleft && x<= xright && y>=ytop && y<=ybottom)
        SetPixel(hdc,x,y,color);
}

int X1,Y1,x2,y2,xc,yc,y,x,Y,k,nume,R,R2,xf,yf,match,x1,y3,xl,yt,xr,yb,xf2,yf2;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    string line;
    vector<int> vect;
    ifstream in;

    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {

    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    case WM_COMMAND:
        switch(wParam)
        {
        case 'one':
            Y=RGB(255,0,0);
            break;
        case 'two':
            Y=RGB(0,0,255);
            break;
        case 'three':
            Y=RGB(0,255,0);
            break;
        case 'five':
            SaveInFile();
            break;
        case 'six':
            in.open("save.txt");
            getline(in, line);
            read(vect, line);
            hdc = GetDC(hwnd);
            savedPoints = vect;
            prev(hdc,vect,Y);
            in.close();
            break;
        case 'seven':
            match=1;
            break;
        case 'Polar':
            match=1;
            break;
        case 'iterative':
            match=2;
            break;
        case 'MidpointCircle':
            match=3;
            break;
        case 'Modified':
            match=4;
            break;
        case 'DDA':
            match=5;
            break;
        case 'MidpointLine':
            match=6;
            break;
        case 'Parametric':
            match=7;
            break;
        case 'first':
            nume=1;
            break;
        case 'second':
            nume=2;
            break;
        case 'third':
            nume=3;
            break;
        case 'fourth':
            nume=4;
            break;
        case 'fifth':
            nume=5;
            break;
        case 'clear':
            ShowWindow(hwnd, SW_HIDE);
            int h;
            /*cout<<"Press 1 to clean open the screen"<<endl;
            cin>>h;
            if(h==1){
            // ShowWindow(hwnd, SW_SHOW);
            ShowWindow(hwnd, SW_RESTORE);
            }*/
            //ShowWindow(hwnd, SW_SHOWNA);
            //ShowWindow(hwnd, SW_SHOWDEFAULT);
            ShowWindow(hwnd, SW_RESTORE);
            clearScreen();
            break;
        case 'rectangle':
            match=12;
            break;
        case 'clipLin':
            match=8;
            break;
        case 'clipPoint':
            match=9;
            break;
        case 'Dir':
            match=10;
            break;
        case 'Pol':
            match=11;
            break;
        }
    case WM_LBUTTONDBLCLK:
        xl=LOWORD(lParam);
        yt=HIWORD(lParam);
        break;
    case WM_RBUTTONDBLCLK:
        xr=LOWORD(lParam);
        yb=HIWORD(lParam);
        cout<<xl<<" "<<yt<<" "<<xr<<" "<<yb<<endl;
        if(match==12)
        {
            Rectangle(hdc,xl,yt,xr,yb);
        }
        xf=xl;
        yf=yt;
        xf2=xr;
        yf2=yb;
        break;
    case WM_LBUTTONDOWN:
        xc=LOWORD(lParam);
        yc=HIWORD(lParam);
        X1=LOWORD(lParam);
        Y1=HIWORD(lParam);
        if(match==9)
        {
            PointClipping(hdc,X1,Y1,xf,yf,xf2,yf2,Y);
        }
        break;
    case WM_RBUTTONDOWN:
        x2=LOWORD(lParam);
        y2=HIWORD(lParam);
        R = Round(sqrt(pow(x2-xc,2.0)+pow(y2-yc,2.0)));
        if(match==1)
        {
            DirectPolar(hdc,xc,yc,R,Y);
        }
        if(match==1&&nume==1)
        {
            DirectPolar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),1);
        }
        if(match==1&&nume==2)
        {
            DirectPolar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),2);
        }
        if(match==1&&nume==3)
        {
            DirectPolar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),3);
        }
        if(match==1&&nume==4)
        {
            DirectPolar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),4);
        }
        if(match==1&&nume==5)
        {
            DirectPolar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),5);
        }

        if(match==2)
        {
            polar(hdc,xc,yc,R,Y);
        }
        if(match==2&&nume==1)
        {
            polar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),1);
        }
        if(match==2&&nume==2)
        {
            polar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),2);
        }
        if(match==2&&nume==3)
        {
            polar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),3);
        }
        if(match==2&&nume==4)
        {
            polar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),4);
        }
        if(match==2&&nume==5)
        {
            polar(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),5);
        }

        if(match==3)
        {
            midpointCircle(hdc,xc,yc,R,Y);
        }
        if(match==3&&nume==1)
        {
            midpointCircle(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),1);
        }
        if(match==3&&nume==2)
        {
            midpointCircle(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),2);
        }
        if(match==3&&nume==3)
        {
            midpointCircle(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),3);
        }
        if(match==3&&nume==4)
        {
            midpointCircle(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),4);
        }
        if(match==3&&nume==5)
        {
            midpointCircle(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),5);
        }

        if(match==4)
        {
            modifiedMidpoint(hdc,xc,yc,R,Y);
        }
        if(match==4&&nume==1)
        {
            modifiedMidpoint(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),1);
        }
        if(match==4&&nume==2)
        {
            modifiedMidpoint(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),2);
        }
        if(match==4&&nume==3)
        {
            modifiedMidpoint(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),3);
        }
        if(match==4&&nume==4)
        {
            modifiedMidpoint(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),4);
        }
        if(match==4&&nume==5)
        {
            modifiedMidpoint(hdc,xc,yc,R,Y);
            MyFloodFill(hdc,xc,yc,Y,RGB(255,0,0),5);
        }

        if(match==5)
        {
            DDALine(hdc,X1,Y1,x2,y2,Y);
        }
        if(match==6)
        {

            midpoint(hdc,X1,Y1,x2,y2,Y);

        }
        if(match==7)
        {
            parametric(hdc,X1,Y1,x2,y2,Y);
            cout<<X1<<" "<<Y1<<" "<<x2<<" "<<y2<<endl;

        }

        if(match==8)
        {
            CohenSuth(hdc,X1,Y1,x2,y2,xf,yf,xf2,yf2);
            cout<<X1<<" "<<Y1<<" "<<x2<<" "<<y2<<endl;
            cout<<xf<<" "<<yf<<" "<<xf2<<" "<<yf2<<endl;
        }

        if(match==10)
        {
            Ellipse(hdc,X1,Y1,x2,y2);
        }
        if(match==11)
        {
            DrawEllipsePolar(hdc,X1,Y1,x2,y2,Y);
        }

        break;

    //menu
    case WM_CREATE:
        AddMenus(hwnd);
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
void AddMenus(HWND hwnd)
{

    hmenu= CreateMenu();

    HMENU hcolor=CreateMenu();

    HMENU Save=CreateMenu();

    HMENU circle=CreateMenu();

    HMENU line=CreateMenu();

    HMENU FILL=CreateMenu();

    HMENU cleare=CreateMenu();

    HMENU Ellips=CreateMenu();

    HMENU clipping=CreateMenu();

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hcolor,"Shape Color");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)Save,"Save&Load");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)circle,"Circle");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)line,"Line");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)FILL,"FloodFill");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)cleare,"Clear Screen ");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)Ellips,"Ellipse");

    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)clipping,"Clipping");

    AppendMenu(hcolor,MF_STRING,'one',"red");
    AppendMenu(hcolor,MF_STRING,'two',"blue");
    AppendMenu(hcolor,MF_STRING,'three',"green");

    AppendMenu(Save,MF_STRING,'five',"save");
    AppendMenu(Save,MF_STRING,'six',"load");

    AppendMenu(cleare,MF_STRING,'clear',"clear");

    AppendMenu(circle,MF_STRING,'Polar',"Polar");
    AppendMenu(circle,MF_STRING,'iterative',"Iterative");
    AppendMenu(circle,MF_STRING,'MidpointCircle',"Midpoint");
    AppendMenu(circle,MF_STRING,'Modified',"Modified MidPoint");

    AppendMenu(line,MF_STRING,'DDA',"DDA");
    AppendMenu(line,MF_STRING,'MidpointLine',"MidPoint");
    AppendMenu(line,MF_STRING,'Parametric',"Parametric");

    AppendMenu(FILL,MF_STRING,'first',"First Quarter");
    AppendMenu(FILL,MF_STRING,'second',"Second Quarter");
    AppendMenu(FILL,MF_STRING,'third',"Third Quarter");
    AppendMenu(FILL,MF_STRING,'fourth',"Fourth Quarter");
    AppendMenu(FILL,MF_STRING,'fifth',"Full Circle");

    AppendMenu(Ellips,MF_STRING,'Dir',"Direct Ellipse");
    AppendMenu(Ellips,MF_STRING,'Pol',"polar Ellipse");

    AppendMenu(clipping,MF_STRING,'rectangle',"Draw Clipping Window");
    AppendMenu(clipping,MF_STRING,'clipLin',"Line");
    AppendMenu(clipping,MF_STRING,'clipPoint',"Point");

    SetMenu(hwnd,hmenu);
}
