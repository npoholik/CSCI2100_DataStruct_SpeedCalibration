/**********************************************************************************
**  The goal of class  GPSCalibration and its member functions is to process data 
**  from the .txt file and provide information to the user and main 
***********************************************************************************/
#include "GPSCalibration.hpp"
#include <iostream>
#include <fstream>
using namespace std;
//********************************************************************************

// Read in all data from RTK_GPS.txt upon creation
GPSCalibration::GPSCalibration() {
  cout << "Processing RTK_GPS Data Entries: " << endl << endl;

  int n = 0;      // Number of elements
  double ele;     // Floating point value of element 
  ifstream File("RTK_GPS.txt");
  
  // Both arrays will receive the same element, only one will be processed later
  while (n < 99 && File >> ele) {
    GPSData[n] = ele;
    rawData[n] = ele;
    n++;
  }
  File.close();

  findWrongData(GPSData);       // Print and remove data above or below a certain max deviation 
  findNoise(GPSData);           // The noise of the data will be found and stored
  removeNoise(GPSData);         // Noise will be removed elements in GPSData
  cout << "------------------------------" << endl << endl;
}

GPSCalibration::~GPSCalibration() {
  cout << "Deleting GPS Database" << endl;
}

// Time t = 0 is assumed to be zero speed, thus this is a rough approximation of the noise
void GPSCalibration::findNoise(double in[]) {
  noise = GPSData[0]; 
  cout << "The noise of the GPS is ~" << noise << " m/s." << endl;
}

// For this function, inaccurate data is defined as any values that increase or decrease by 5 m/s within a second
void GPSCalibration::findWrongData(double in[]) {
  // Compare each element to its previous
  for (int i = 1; i < 99; i++) {
    double prevSpeed = GPSData[i-1];
    if (((GPSData[i] - prevSpeed) > 5) || ((GPSData[i] - prevSpeed) < -5)) {
      cout << "The speed at time " << i + 1 << " seconds, " << GPSData[i] << "m/s, is inaccurate" << endl;
      GPSData[i] = -1;
      i++;
    }
  }
  cout << endl;
}

// The following function will remove the noise from each data element in GPSData
void GPSCalibration::removeNoise(double in[]) {
  cout << "Removing the noise from the data..." << endl << endl;
  // Subtract stored value of noise from each element
  for (int i = 0; i < 99; i++) {
    GPSData[i] = GPSData[i] - noise;
  }
}

// Print raw data
void GPSCalibration::printData() {
  for (int i = 0; i < 99; i++) {
    cout << "Speed at " << i + 1 << " seconds: " << rawData[i] << " m/s." << endl;
  }
  cout << "------------------------------" << endl << endl;
}

// The following function will return the value of a given index n 
double GPSCalibration::getIndex(int n) {
  return GPSData[n];
}

// The following function will print noise and inaccurate values from the raw data set
void GPSCalibration::printInformation() {
  cout << "The noise of the GPS is ~" << noise << " m/s." << endl << endl;
  // Compare each element to its previous and compare
  for (int i = 1; i < 99; i++) {
    double prevSpeed = rawData[i-1]; 
    if (((rawData[i] - prevSpeed) > 5) || ((rawData[i] - prevSpeed) < -5)) {
      cout << "The speed at time " << i + 1 << " seconds, " << rawData[i] << "m/s, is inaccurate" << endl;
      i++;
    }
  }
}

// The following function will serach the raw data set for a specific speed and return the resulting time in seconds
void GPSCalibration::findSpeed(double val) {
  int castVal = (int)val; // The user can pass a double, but it will be cast to an int for ease in searching
  bool found = false;
  double *dataPtr = rawData;

  for (int i = 0; i < 99; i++) {
    if (((int)*dataPtr) == val) {
      cout << "The speed " << *dataPtr << " was found at time " << i + 1 << " seconds. " << endl;
      found = true;
    }
    dataPtr++; // the pointer is incremented up by one at each iteration to move onto the next element
  }
  if (!found) {
    cout << "Data point could not be found..." << endl;
  }
}