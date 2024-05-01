#ifndef GPSCalibration_hpp
#define GPSCalibration_hpp

class GPSCalibration {
  private:

    double rawData[99]; // stores the raw data from the .txt file
    double GPSData[99]; // will store data adjusted for noise and inaccurate entries
    double noise;       // will store the value of the noise in the dataset

  public:
    GPSCalibration();
    ~GPSCalibration();

    void findNoise(double in[]);
    void findWrongData(double in[]);
    void removeNoise(double in[]);      // Adjusts a data set for noise 
    void printData();                   //Print all raw values from the RTK_GPS.txt
    void printInformation();            // Prints noise and inaccurate data points
    double getIndex(int n);             // will return the value at a given passed index
    void findSpeed(double val);
};
#endif /*GPSCalibration_hpp */