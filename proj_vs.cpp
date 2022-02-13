#include<iostream>
#include<math.h>
#include<iomanip>
#include<fstream>

using namespace std;

struct motionInfo{ double Vx, VT, Vy, Ax, Ay, x, y;
};


int count;
const double g=9.81;
const double k_m = 8.71e-3;	
motionInfo motionData;

//function prototypes
void getInit();
double calcV(double, double);
double calcVT(double, double);
double calcAx(double, double);
double calcAy(double, double);
double calcpos(double, double);
void printData(int);
void writeData();

double t;


int main(){
	//This program generates the trajectory of a projectile lauched at an angle under the influence of gravity
	//It will take th desired iteration interval and the initial velocities from user
	getInit();
	

	motionData.VT=calcVT(motionData.Vx, motionData.Vy);
	motionData.Ax=calcAx(motionData.VT, motionData.Vx );
	motionData.Ay= calcAy(motionData.VT, motionData.Vy);
	printData(count);
//	writeData();
	
	while(motionData.y>=0){
		motionData.x += calcpos(motionData.Vx, motionData.Ax);
		motionData.y += calcpos(motionData.Vy, motionData.Ay);
		motionData.Vx= calcV(motionData.Vx, motionData.Ax);
		motionData.Vy= calcV(motionData.Vy, motionData.Ay);
		motionData.VT= calcVT(motionData.Vx, motionData.Vy);
		motionData.Ax = calcAx(motionData.VT, motionData.Vx);
		motionData.Ay= calcAy(motionData.VT, motionData.Vy);
		printData(++count);
//		writeData();
}
	
		
	return 0;
}


//fucntion definitions
void getInit(){
	cout<< "Enter the x-vel: ";
	cin>>motionData.Vx;
	
	cout<< "Enter the y-vel: ";
	cin>>motionData.Vy;
	
	cout<< "Enter the time interval: ";
	cin>>t;
	
	cout<< "Enter the initial x-position: ";
	cin>>motionData.x;
	
	cout<< "Enter the initial y-position: ";
	cin>>motionData.y;
}

double calcV(double u, double a){
	return u + (a*t);
}

double calcVT(double Vx, double Vy){
	return sqrt((Vx*Vx)+(Vy*Vy));
}

double calcAx(double V, double Vx){
	return -k_m*V*Vx;
}

double calcAy(double v, double vy){
	return -g-(k_m*v*vy);
}

double calcpos(double u, double a){
	return u*t + ((a*t*t)/2);
}

void printData(int c){
	cout<< fixed << setprecision(6);
	cout<<"=============|Iteration No: "<< c + 1<< "|Time: "<<c*t<<" |============="<<endl
		<<"\t\t\tVx: "<<motionData.Vx<<" m/s"<<endl
		<<"\t\t\tVy: "<<motionData.Vy<<" m/s"<<endl
		<<"\t\t\tVT: "<<motionData.VT<<" m/s"<<endl
		<<"\t\t\tAx: "<<motionData.Ax<<" m/s^2"<<endl
		<<"\t\t\tAx: "<<motionData.Ay<<" m/s^2"<<endl
		<<"\t\t\tX: "<<motionData.x<<" m"<<endl
		<<"\t\t\tY: "<<motionData.y<<" m"<<endl
		<< "\t\t\t"<<endl;
}


void writeData(){
	fstream writer;
	writer.open("database.txt", ios::app);
	if(writer.is_open()){
  writer<<"=============|Iteration No: "<< count + 1<< "|Time: "<<count*t<<" |============="<<endl
		<<"\t\t\tVx: "<<motionData.Vx<<" m/s"<<endl
		<<"\t\t\tVy: "<<motionData.Vy<<" m/s"<<endl
		<<"\t\t\tVT: "<<motionData.VT<<" m/s"<<endl
		<<"\t\t\tAx: "<<motionData.Ax<<" m/s^2"<<endl
		<<"\t\t\tAx: "<<motionData.Ay<<" m/s^2"<<endl
		<<"\t\t\tX: "<<motionData.x<<" m"<<endl
		<<"\t\t\tY: "<<motionData.y<<" m"<<endl
		<<"\n";
		writer.close();
	}
	
}

