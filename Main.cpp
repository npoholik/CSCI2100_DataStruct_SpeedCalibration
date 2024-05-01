/*********************************************************************************
**  The goal of the main function is to create an organized terminal UI that allows 
**  the user to access all relevant information. This will be accomplished by incorporating
**  the previously defined smartWatchCalibration files and GPSCalibration files 
**********************************************************************************/
#include "GPSCalibration.hpp"
#include "smartWatchCalibration.hpp"
#include <iostream>
#include <vector>
using namespace std;
//********************************************************************************

void calculateSpeed(GPSCalibration &gps,            // Averages out calibrated data and stores it in a vector for user
smartWatchCalibration &watch, vector<double> &in);
void printSpeed(vector<double> &in);                // Print calculated speed to user
void calculateAcceleration(vector<double> &in, int seconds);

//********************************************************************************

int main() {
  vector<double> accurateSpeed;
  // Initialize the objects for smartWatch and GPS
  GPSCalibration gpsData;
  smartWatchCalibration watchData;
  
  // Calculate & print more accurate values based on datasets 
  calculateSpeed(gpsData, watchData, accurateSpeed);
  printSpeed(accurateSpeed);

  char select = '0'; // User menu selection
  int attempts = 0;  // Tracks failed attempts at menu selection

  while(true) {
    cout << "Menu Options: " << endl << 
    "1. Reprint the Actual Speed" << endl << 
    "2. Reprint GPS Noise and Inaccurate Speeds" << endl << 
    "3. Reprint Smart Watch Noise and Inaccurate Speeds" << endl << 
    "4. Print All Raw GPS Data" << endl << 
    "5. Print All Raw Smart Watch Data" << endl << 
    "6. Search for a Speed" << endl << 
    "7. Calculate Acceleration for a Given Time" << endl << 
    "8. Exit Program" << endl;

    cout << endl << "Make your selection: ";
    cin >> select;
    cout << "------------------------------" << endl << endl;

    // Quit program condition
    if (select == '8' || attempts > 8) {
      cout << "Exiting Program..." << endl;
      break;
    }
    // Reprint actual speed data
    else if (select == '1') {
      cout << endl;
      printSpeed(accurateSpeed);
    }
    // Reprint GPS noise and inaccurate speeds
    else if (select == '2') {
      gpsData.printInformation();
      cout << "------------------------------" << endl << endl;
    }
    // Reprint smart watch noise and inaccurate speeds
    else if (select == '3') {
      watchData.printInformation();
      cout << "------------------------------" << endl << endl;
    }
    //Print RAW GPS Data
    else if (select == '4') {
      gpsData.printData();
    }
    // Print RAW Smart Watch Data
    else if (select == '5') {
      watchData.printData();
    }

    // Speed Search
    else if (select == '6') {
      char data = NULL;
      cout << "Search the GPS Dataset or Smart Watch Dataset? G/W" << endl;
      cin >> data;
      // If the user inputs anything except G/W, then the program will throw an error
      if (data != 'G' && data != 'g' && data != 'W' && data != 'w') {
        cout << "Error: Invalid Input" << endl;
      }
      else if (data == 'G' || data == 'g') {
        double val;
        cout << "Input the value to search in the GPS Dataset: ";
        cin >> val;
        gpsData.findSpeed(val);
      }
      else if (data == 'W' || data == 'w') {
        double val;
        cout << "Input the value to search in the Smart Watch Dataset: ";
        cin >> val;
        watchData.findSpeed(val);
      }
      // Error where no previous if gets triggered (should be impossible)
      else {
        cout << "An error has occured." << endl;
      }
      cout << "------------------------------" << endl << endl;
    }

    // Calculate acceleration for time t
    else if (select == '7') {
      int secondsInput = NULL;
      cout << "Input the time (in seconds) you want to find the acceleration at: ";
      cin >> secondsInput;
      calculateAcceleration(accurateSpeed, secondsInput);
      cout << "------------------------------" << endl << endl;
    }
    //Invalid attempt case
    else {
      cout << "Error: Invalid Selection, Try Again" << endl;
      attempts++;
    }
  }
  
}

void calculateSpeed(GPSCalibration &gps, smartWatchCalibration &watch, vector<double> &in) {
  in.push_back(0); // Zero will be the first value pushed to the back of the vector, as it is the correct value at 0 seconds
  double speed; // Stores calculated value from two data sets 

    for (int i = 1; i < 99; i++) {
      // If both datasets have accurate data
      if ((gps.getIndex(i) >= 0) && (watch.getIndex(i) >= 0)) {
        speed = (gps.getIndex(i) + watch.getIndex(i)) / 2.0;      // Find average
        in.push_back(speed);
      }
      // If GPS is accurate and smart watch is inaccurate
      else if(gps.getIndex(i) >= 0 && watch.getIndex(i) < 0) {
        speed = gps.getIndex(i);
        in.push_back(speed);
      }
      // If smart watch is accurate and GPS is inaccurate
      else if(gps.getIndex(i) < 0 && watch.getIndex(i) >= 0) {
        speed = watch.getIndex(i);
        in.push_back(speed);
     }
      // -1 represents both datasets 
      else {
        cout << "INVALID SPEED READING" << endl;
        in.push_back(-1.0);
    }
  }
}

void printSpeed(vector<double> &in) {
  cout << "Printing the Calculated Accurate Speeds: " << endl;
  for (int i = 0; i < 99; i++) {
    cout << "Speed at " << i + 1 << " seconds: " << in.at(i) << " m/s." << endl;
  }
  cout << "------------------------------" << endl << endl;
}


void calculateAcceleration(vector<double> &in, int seconds) {
  cout << endl;
  // a = 0 m/s^2 at time = 1 (no movement yet)
  if (seconds == 1) {
    cout << "Acceleration is 0 m/s^2 at 1 second." << endl;
  }
  // Out of bounds error
  else if (seconds > 99 || seconds < 1) {
    cout << "Time is out of bounds. Acceleration is unknown" << endl;
  }
  else {
    // Acceleration is defined as change in speed over change in time
    double accel = (in.at(seconds - 1) - in.at(seconds - 2)) / ((seconds - 1) - (seconds - 2));
    cout << "Acceleration is " << accel << " m/s^2 at " << seconds << " seconds." << endl;
  }
}