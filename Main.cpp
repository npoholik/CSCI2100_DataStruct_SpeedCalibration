/* The goal of the main function is to create an organized UI that allows the user to access all relevant information
  This will be accomplished by incorporating the previously defined smartWatchCalibration files and GPSCalibration files 
*/

#include "GPSCalibration.hpp"
#include "smartWatchCalibration.hpp"
#include <iostream>
#include <vector>
using namespace std;

// The following function  will calculate the actual speed of the vehicle based off of gps data and watch data, and push it to a vector
void calculateSpeed(GPSCalibration &gps, smartWatchCalibration &watch, vector<double> &in);

// The following function will print the actual speed data from a vector
void printSpeed(vector<double> &in);

// The following function will calculate the acceleration based on the actual speed at a specific  time in seconds
void calculateAcceleration(vector<double> &in, int seconds);


int main() {
  vector<double> accurateSpeed; // A vector of datatype double is initialized; this will store the actual speeds
  
  GPSCalibration gpsData; // A GPSCalibration object is initialized to store the data of the GPS data
  smartWatchCalibration watchData; // A smartWatchCalibration is initialized to store the data of the watch data
  
  calculateSpeed(gpsData, watchData, accurateSpeed); // calculateSpeed is called, with objects gpsData, watchData passed as well as the vector accurateSpeed
  // This will result in the vector accurateSpeed now holding the accurate values

  printSpeed(accurateSpeed); // printSpeed is called, which will print all the values now stored in the vector accurateSpeed

  char select = '0'; // A char is initialized that will determine what menu options the user selects
  int attempts = 0; // An int is initialized that will determine how many error attempts are thrown
  // This allows for an emergency exit option for the program 

  // The following while loop will iterate infinitely unless explicitly quit or attempts exceeds 8
  while(true) {

    // The following prints out the menu options to the user
    cout << "Menu Options: " << endl << "1. Reprint the Actual Speed" << endl << "2. Reprint GPS Noise and Inaccurate Speeds" << endl << "3. Reprint Smart Watch Noise and Inaccurate Speeds" << endl << "4. Print All Raw GPS Data" << endl << "5. Print All Raw Smart Watch Data" << endl << "6. Search for a Speed" << endl << "7. Calculate Acceleration for a Given Time" << endl << "8. Exit Program" << endl;

    // The user is asked for their input, and the selection is stored in select
    cout << endl << "Make your selection: ";
    cin >> select;
    cout << "------------------------------" << endl << endl;

    // The following if statements will determine the menu option and perform the subsequent commands associated

    // If the user inputs 8 or attempts exceed 8 tries, the program will automatically quit and inform the user
    if (select == '8' || attempts > 8) {
      cout << "Exiting Program..." << endl;
      break;
    }

    // If the user inputs 1, printSpeed is called with accurateSpeed vector passed
    // This will once again print out the accurate speed data to the user
    else if (select == '1') {
      cout << endl;
      printSpeed(accurateSpeed);
    }
      
    // If the user inputs 2, then the GPS noise and inaccurate data information is printed out to the user
    // This is accomplished with a call to printInformation()
    else if (select == '2') {
      gpsData.printInformation();
      cout << "------------------------------" << endl << endl;
    }

    // If the user inputs 3, then the Smart Watch noise and inaccurate data information is printed to the user
    // This is accomplished with a call to printInformation()
    else if (select == '3') {
      watchData.printInformation();
      cout << "------------------------------" << endl << endl;
    }

    // If the user inputs 4, then the raw data of the GPS is printed to the user
    // This is accomplished with a call to printData()
    else if (select == '4') {
      gpsData.printData();
    }

    // If the user inputs 5, then the raw data of the Smart Watch is printed to the user
    // This is accomplished with a call to printData()
    else if (select == '5') {
      watchData.printData();
    }

    // If the user inputs 6, then they will be prompted to search either the GPS or smart watch and input a value to find
    // This is accomplished with a call to findSpeed(val), which will look for the truncated value of what the user passed in the data set of either the GPS or smart watch
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
      // If no previous statements are triggered, then an unknown error message is printed 
      else {
        cout << "An error has occured." << endl;
      }
      cout << "------------------------------" << endl << endl;
    }

    // If the user inputs 7, then they will be prompted to input a time to calculate the acceleration at
    // The acceleration will then be calculated through a call to calculateAcceleration
    else if (select == '7') {
      int secondsInput = NULL;
      cout << "Input the time (in seconds) you want to find the acceleration at: ";
      cin >> secondsInput;
      calculateAcceleration(accurateSpeed, secondsInput);
      cout << "------------------------------" << endl << endl;
    }

    // If the user inputs no valid inputs to the menu, then an error will be thrown 
    // For each error, attempts is incremented by one
    // If attempts exceeds 8, the program automatically quits to avoid potential infinite loops
    else {
      cout << "Error: Invalid Selection, Try Again" << endl;
      attempts++;
    }
  }
  
}


void calculateSpeed(GPSCalibration &gps, smartWatchCalibration &watch, vector<double> &in) {
  in.push_back(0); // Zero will be the first value pushed to the back of the vector, as it is the correct value at 0 seconds
  
  double speed; // A double variable speed is initialized to store the value calculated from the GPS and smart watch data

    // The following for loop will iterate 98 - 1 times so that each data value can be accurately calculated
    for (int i = 1; i < 99; i++) {
      // The first if statement will trigger if both the gps and watch have accurate data elements at that index
      if ((gps.getIndex(i) >= 0) && (watch.getIndex(i) >= 0)) {
        // The speed will then be calculated by taking the average of these two data elements, which will then be pushed to the back of the vector
        speed = (gps.getIndex(i) + watch.getIndex(i)) / 2.0;
        in.push_back(speed);
      }
      // The second if statement will trigger if only the gps has accurate data and the watch data is inaccurate
      else if(gps.getIndex(i) >= 0 && watch.getIndex(i) < 0) {
        // The speed will then be set equal to the gps value and pushed to the back of the vector
        speed = gps.getIndex(i);
        in.push_back(speed);
      }
      // The third if statement will trigger if only the watch has accurate data and the gps data is inaccurate
      else if(gps.getIndex(i) < 0 && watch.getIndex(i) >= 0) {
        // The speed will then be set equal to the watch value and pushed to the back of the vector
        speed = watch.getIndex(i);
        in.push_back(speed);
     }
      // If both the watch and gps have inaccurate data readings, then an invalid speed reading will be printed and the value pushed to the vector will be -1
      else {
        cout << "INVALID SPEED READING" << endl;
        in.push_back(-1.0);
    }
  }
}


void printSpeed(vector<double> &in) {
  cout << "Printing the Calculated Accurate Speeds: " << endl;
  // The following will iterate through the size of the vector and print the actual speed at all indices
  for (int i = 0; i < 99; i++) {
    cout << "Speed at " << i + 1 << " seconds: " << in.at(i) << " m/s." << endl;
  }
  cout << "------------------------------" << endl << endl;
}


void calculateAcceleration(vector<double> &in, int seconds) {
  cout << endl;
  // If the time passed to the function is 1, then acceleration is 0 m/s^2 as the vehicle has not begun moving yet
  if (seconds == 1) {
    cout << "Acceleration is 0 m/s^2 at 1 second." << endl;
  }
  // If the time passed to the function is out of bounds, then a message will be printed indicating that to the user
  else if (seconds > 99 || seconds < 1) {
    cout << "Time is out of bounds. Acceleration is unknown" << endl;
  }
  // If no other if statements trigger, then the acceleration will be calculated 
  else {
    // Acceleration is defined as change in speed over change in time, thus the speed at the current time minus the speed at the previous time over the difference of their respect indices will yield the acceleration
    // The value will then be printed out to the user 
    double accel = (in.at(seconds - 1) - in.at(seconds - 2)) / ((seconds - 1) - (seconds - 2));
    cout << "Acceleration is " << accel << " m/s^2 at " << seconds << " seconds." << endl;
  }
}