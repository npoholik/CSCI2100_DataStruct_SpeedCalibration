#ifndef GPSCalibration_hpp
#define GPSCalibration_hpp

class GPSCalibration {
  private:

    double rawData[99]; // stores the raw data from the .txt file
    double GPSData[99]; // will store data adjusted for noise and inaccurate entries
    double noise;  // will store the value of the noise in the dataset

  public:

    GPSCalibration(); // constructor

    ~GPSCalibration(); // destructor

    void findNoise(double in[]); // will take a dataset in and find the approximate noise

    void findWrongData(double in[]); // will take a dataset in and find inaccurate entires

    void removeNoise(double in[]); // will take the dataset and adjust for the noise 

    void printData(); // will print all raw values from the RTK_GPS.txt

    void printInformation(); // will print the noise and inaccurate values

    double getIndex(int n); // will return the value at a given passed index

    void findSpeed(double val); // will search the data for a specific speed

};
#endif /*GPSCalibration_hpp */