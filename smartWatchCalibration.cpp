/****************************************************************************
**  The goal of smartWatchCalibration and its member functions is to process data
**  from the .txt file and provide information to the user and main 
*****************************************************************************/
#include "smartWatchCalibration.hpp"
#include <iostream>
#include <fstream>
using namespace std;
//***************************************************************************

smartWatchCalibration::smartWatchCalibration() {
    cout << "Processing Smart Watch Data Entries: " << endl << endl;

    int n = 0;      // Number of elements
    double ele;     // Floating point value of element 
    ifstream File("SmartWatch.txt");

    // Both arrays will receive the same element, only one will be processed later
    while (n < 99 && File >> ele) {
        watchData[n] = ele;
        rawData[n] = ele;
        n++;
    }
    File.close();
    findWrongData(watchData);     // Print and remove data above or below a certain max deviation 
    findNoise(watchData);         // The noise of the data will be found and stored
    removeNoise(watchData);       // Noise will be removed elements in GPSData
    cout << "------------------------------" << endl << endl;
}

smartWatchCalibration::~smartWatchCalibration() {
    cout << "Deleting Smart Watch Database" << endl;
}

// Time t = 0 is assumed to be zero speed, thus this is a rough approximation of the noise
void smartWatchCalibration::findNoise(double in[]) {
    noise = watchData[0];
    cout << "The noise of the Smart Watch is ~" << noise << " m/s." << endl;
}

// For this function, inaccurate data is defined as any values that increase or decrease by 5 m/s within a second
void smartWatchCalibration::findWrongData(double in[]) {
    // Compare each element to its previous
    for (int i = 1; i < 99; i++) {
        double prevSpeed = watchData[i-1];
        if (((watchData[i] - prevSpeed) > 10) || ((watchData[i] - prevSpeed) < -10)) {
            cout << "The speed at time " << i + 1 << " seconds, " << watchData[i] <<
            "m/s, is inaccurate" << endl;
            watchData[i] = -1;
            i++;
        }
    }
    cout << endl;
}

// The following function will remove the noise from each data element in watch data
void smartWatchCalibration::removeNoise(double in[]) {
    cout << "Removing the noise from the data..." << endl << endl;
    // Subtract stored value of noise from each element
    for (int i = 0; i < 99; i++) {
        watchData[i] = watchData[i] - noise;
    }
}

// Print raw data
void smartWatchCalibration::printData() {
    for (int i = 0; i < 99; i++) {
        cout << "Speed at " << i + 1 << " seconds: " << rawData[i] << " m/s." << endl;
    }
    cout << "------------------------------" << endl << endl;
}

// The following function will return the value of a given index n 
double smartWatchCalibration::getIndex(int n) {
    return watchData[n];
}

// The following function will print noise and inaccurate values from the raw data set
void smartWatchCalibration::printInformation() {
    cout << "The noise of the Smart Watch is ~" << noise << " m/s." << endl << endl;
      // Compare each element to its previous and compare
    for (int i = 1; i < 99; i++) {
        double prevSpeed = rawData[i-1];
        if (((rawData[i] - prevSpeed) > 10) || ((rawData[i] - prevSpeed) < -10)) {
            cout << "The speed at time " << i + 1 << " seconds, " << rawData[i] << "m/s, is inaccurate" << endl;
            i++;
        }
    }
}

// The following function will serach the raw data set for a specific speed and return the resulting time in seconds
void smartWatchCalibration::findSpeed(double val) {
    int castVal = (int)val; // The user can pass a double, but it will be cast to an int for ease in searching
    bool found = false;
    double *dataPtr = rawData;

    for (int i = 0; i < 99; i++) {
        if (((int)*dataPtr) == val) {
            cout << "The speed " << *dataPtr << " was found at time " << i + 1 << "seconds. " << endl;
            found = true;
        }
        dataPtr++; // the pointer is incremented up by one at each iteration to move onto the next element
    }
    if (!found) {
        cout << "Data point could not be found..." << endl;
    }
}