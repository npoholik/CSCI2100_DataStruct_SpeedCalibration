/* The goal of smartWatchCalibration and its member functions is to process data
from the .txt file and provide information to the user and main */
#include "smartWatchCalibration.hpp"
#include <iostream>
#include <fstream>
using namespace std;

// The following is the constructor for the smartWatchCalibration object
smartWatchCalibration::smartWatchCalibration() {
    cout << "Processing Smart Watch Data Entries: " << endl << endl;
    int n = 0; // represents the number of elements in the .txt
    double ele; // stores an individual element from the .txt
    ifstream File("SmartWatch.txt"); // Opens the SmartWatch.txt file to reading for the compiler
    // The following while loop will iterate through the .txt file, adding each element to watchData and rawData arrays at each iteration
    while (n < 99 && File >> ele) {
        watchData[n] = ele;
        rawData[n] = ele;
        n++;
    }
    File.close(); // The file is closed to any more reading
    findWrongData(watchData); // The inaccurate data is found in the watchData array, which will remove these values after printing them
    findNoise(watchData); // The noise of the data will be found and stored in the member variable noise
    removeNoise(watchData); // The value of the noise will be removed from each speed element stored in watchData
    cout << "------------------------------" << endl << endl;
}

// The following is the destructor for the smartWatchCalibration object
smartWatchCalibration::~smartWatchCalibration() {
    cout << "Deleting Smart Watch Database" << endl; // Simply print out a deletion message to the user
}

//The following function will find the noise in a dataset
void smartWatchCalibration::findNoise(double in[]) {
    noise = watchData[0]; // The value at index 0 represents the approx noise, as it is assumed that in the first second speed is 0 m/s
    cout << "The noise of the Smart Watch is ~" << noise << " m/s." << endl; // Print out the value found to the user
}

// The following function will find any inaccurate data in the dataset
// For this function, inaccurate data is defined as any values that increase or decrease by 10 m/s within a second
    void smartWatchCalibration::findWrongData(double in[]) {
    // The following for loop will iterate 98 - 1 times, as it must compare the previous element for each iteration
    for (int i = 1; i < 99; i++) {
        double prevSpeed = watchData[i-1]; // This will store the previous speed element
        // The following if will see if the difference between the current speed and previous speed is > 10 or < -10
        // If the difference is greater or less than, then the speed will be printed to the user
        if (((watchData[i] - prevSpeed) > 10) || ((watchData[i] - prevSpeed) < -10)) {
            cout << "The speed at time " << i + 1 << " seconds, " << watchData[i] <<
            "m/s, is inaccurate" << endl;
            watchData[i] = -1; // The index of the inaccurate data will be replaced with -1 (assuming only positive velocity vectors, this allows for the data to be differentiated in main)
            i++; // i is incremented by one to avoid double comparison with the inaccurate data
        }
    }
    cout << endl;
}
// The followiung function will remove the noise from each data element in watchData
void smartWatchCalibration::removeNoise(double in[]) {
cout << "Removing the noise from the data..." << endl << endl;
// The following for loop will iterate through the dataset and subtract the noise value from each speed
    for (int i = 0; i < 99; i++) {
        watchData[i] = watchData[i] - noise;
    }
}

// The following function will print all the data elements of the raw data
void smartWatchCalibration::printData() {
    // The following for loop will iterate through the dataset of rawData and print each element
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
    // The noise will first be printed out
    cout << "The noise of the Smart Watch is ~" << noise << " m/s." << endl << endl;
    // The following for loop will iterate 98 - 1 times, as it must compare the previous element for each iteration
    for (int i = 1; i < 99; i++) {
        double prevSpeed = rawData[i-1]; // This will store the previous speed element to current index
        // The following if will see if the difference between the current speed and previous speed is > 10 or < -10
        // If the difference is greater or less than, then the speed will be printed to the user
        if (((rawData[i] - prevSpeed) > 10) || ((rawData[i] - prevSpeed) < -10)) {
            cout << "The speed at time " << i + 1 << " seconds, " << rawData[i] << "m/s, is inaccurate" << endl;
            i++; // avoids double comparison
        }
    }
}
// The following function will search the raw data set for a specific speed and return the resulting time in seconds
void smartWatchCalibration::findSpeed(double val) {
    int castVal = (int)val; // The user can pass a double, but it will be cast to an int for ease in searching
    bool found = false; // The following boolean value will determine whether a value was found or not
    double *dataPtr = rawData; // The following will create a pointer that points to the first element of rawData
    // The following for loop will iterate throughout the entire dataset
    for (int i = 0; i < 99; i++) {
    // At each iteration, the current value of the pointer (cast to an int) will be compared to val
    // If they are equal, the speed and time it occurs will be printed out to the user
        if (((int)*dataPtr) == val) {
            cout << "The speed " << *dataPtr << " was found at time " << i + 1 << "seconds. " << endl;
            found = true;
        }
            dataPtr++; // the pointer is incremented up by one at each iteration to move onto the next element
    }
    // If no element was found, then bool found will be false and the following if statement will print a message to the user that the speed could not be found
    if (!found) {
        cout << "Data point could not be found..." << endl;
    }
}