

#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>


 double Bez(double p0,double p1, double p2, double p3, double t)
{
	
	 return ((1 - t) * (1 - t) * (1 - t) * p0) + (3 * t*(1 - t) * (1 - t) * p1) + (3 * t * t * (1 - t)*p2) + (t * t * t * p3);
}
 void  DrawBaseLines(double PointA[], double PointB[], double PointC[], double PointD[])
 {
	 glBegin(GL_LINE_STRIP);
	 glVertex3dv(PointA);
	 glVertex3dv(PointB);

	 glVertex3dv(PointD);
	 glVertex3dv(PointC);
	 glEnd();
	 

 }
 void DrawBez(double PointA[], double PointB[], double PointC[], double PointD[])
 {
	 double P[3];
	 DrawBaseLines(PointA, PointB, PointC, PointD);
	 glBegin(GL_LINE_STRIP);
	 for (double i = 0; i < 1.0001; i = i + 0.01)
	 {
		 P[0] = Bez(PointA[0], PointB[0], PointC[0], PointD[0], i);
		 P[1] = Bez(PointA[1], PointB[1], PointC[1], PointD[1], i);
		 P[2] = Bez(PointA[2], PointB[2], PointC[2], PointD[2], i);
		 glVertex3dv(P);
	 }
	 glEnd();
 }

 double* Erm(double VecA[], double VecA1[]  , double VecC[] , double VecC1[], double t)
 {
	 double Result[3];
	 for(int i=0;i<3;i++)

         Result[i]=VecA[i] * (2 * t * t * t - 3 * t * t + 1) + VecC1[i]*(-2 * t * t * t + 3 * t * t) + VecA1[i] * (t * t * t - 2 * t * t + t) + VecC[i]*(t * t * t - t * t);
	 return Result;
 }


 void DrawBaseVecs(double PointA[], double PointB[], double PointC[], double PointD[])
 {
	
	 glBegin(GL_LINES);
	 glVertex3dv(PointA);
	 glVertex3dv(PointB);
	 glVertex3dv(PointC);
	 glVertex3dv(PointD);
	 glEnd();

	 glColor3d(1, 0, 1);
	 glBegin(GL_POINTS);
	 glVertex3dv(PointA);
	 glVertex3dv(PointC);
	 glEnd();
 }
 void DrawErm(double PointA[], double PointB[], double PointC[], double PointD[])
 {
	 double P[3];
	 double VecAB[] = {PointB[0]-PointA[0], PointB[1]-PointA[1],PointB[2] - PointA[2] };
	 double VecCD[] = { PointD[0] - PointC[0], PointD[1] - PointC[1],PointD[2] - PointC[2] };
	 DrawBaseVecs(PointA, PointB, PointC, PointD);
	 glBegin(GL_LINE_STRIP);
	 for (double i = 0; i < 1.0001; i = i + 0.01)
	 {
		 P[0] = *(Erm(PointA, VecAB, VecCD,   PointC, i));
		 P[1] = *(Erm(PointA, VecAB, VecCD,  PointC, i) +1);
		 P[2] = *(Erm(PointA, VecAB, VecCD,  PointC, i) +2);
		 glColor3d(0, 0, 0);
		 glVertex3dv(P);
	 }
	 glEnd();


	
 }

void Render(double delta_time)
{
	
	double PointA[] = { 2, 3, 0 };
	double PointB[] = { 6, 1,0 };
	double PointC[] = { 5, 7, 0 };
	double PointD[] =  { 9, 7, 0 };

	
	DrawErm(PointA, PointB, PointC, PointD);
	DrawBez(PointA, PointB, PointC, PointD);
	/*double PointA1[] = { 5, 8, 0 };
	double PointB1[] = { 6.5, 13,0 };
	double PointC1[] = { 14, 3.5, 0 } ;
	double PointD1[] = { 13, 8.5, 0 };
	DrawBez(PointA1, PointB1, PointC1, PointD1);
	DrawErm(PointA1, PointB1, PointC1, PointD1);*/
};



