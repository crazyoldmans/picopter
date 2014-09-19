//Author:	Michael Baxter 	20503664@student.uwa.edu.au
//Author:	Omid Targhagh 	20750454@student.uwa.edu.au
//Date:		18-9-2014
//Version:	v1.3
//
//Desciption:	Class used for gps.  Starts gps data reading thread which saves data in this object.

#ifndef __RUN_LAWNMOWER_INCLUDED__
#define __RUN_LAWNMOWER_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <ctime>

#include <gpio.h>
#include <flightBoard.h>
#include <gps_qstarz.h>		//This will be changed later when Piksi has been integrated
#include <imu_euler.h>
#include <cmt3.h>
#include <sstream>
#include <ncurses.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "camera.h"

using namespace std;

#define HMIN 320
#define HMAX 40
#define SMIN 95
#define SMAX 255
#define VALMIN 95	//VMIN already used
#define VALMAX 255
#define REDTHRESH 50	//Number of red pixels need to see in an image
#define FRAME_WAIT 11 	//Number of frames to wait

#define SWEEP_SPACING 6		//Distance between parallel sweeps in m
#define SPACING 3 			//Separation between intermediate points
#define LOCATION_WAIT 0		//Time in ms Copter waits at each point
#define LOOP_WAIT 100 		//Time in ms Copter wait in each loop
#define GPS_DATA_FILE "config/waypoints_list.txt"
#define WAYPOINT_RADIUS 1.200		//In m - needs to be large enough that can speed not too low

#define KPh 10				//Horizontal proportional controller constant - 8 seems to be too small
#define SPEED_LIMIT 35		//Percentage

#define OVAL_IMAGE_PATH "../picopter-base/config/James_Oval.png"
#define MAXLAT -31.979422	//Properties of image file of James Oval & represent min & max corners - are in degrees
#define MINLON 115.817162
#define MINLAT -31.980634
#define MAXLON 115.818709
#define PIXEL_RADIUS 1 		//Number of surrounding pixels to turn 'Red'. Can probably be left as 0, unless get really fine image.

/*Things needed for 'flyTo'*/
//---------------------------
#define PI 3.14159265359
#define RADIUS_OF_EARTH 6364963	//m
#define sin2(x) (sin(x)*sin(x))
#define DIRECTION_TEST_SPEED 40
#define DIRECTION_TEST_DURATION 6000

typedef struct{		//These are in degrees now.
	double lat;
	double lon;
} Pos;

void run_lawnmower(FlightBoard*, GPS*, GPS_Data*, IMU*, IMU_Data*, Pos, Pos);
double calculate_distance(Pos, Pos);
double calculate_bearing(Pos, Pos);
void setLawnCourse(FB_Data*, double, double, double);
void populateMainVector(vector<Pos>*, Logger*, Pos, Pos);
void addPoints(vector<Pos>*, Pos, Pos, int);
void flyTo(FlightBoard*, GPS*, GPS_Data*, IMU*, IMU_Data*, double, double, double, Logger*, Logger* , RaspiCamCvCapture*, int, Mat);
double determineBearing(FlightBoard*, GPS*, GPS_Data*);

void captureImage(int, GPS_Data*);
bool checkRed(Mat, Logger*);
double redComDist(Mat);
void updatePicture(Mat, double, double);
void terminateLawn(int);

#endif// __RUN_LAWNMOWER_INCLUDED__
