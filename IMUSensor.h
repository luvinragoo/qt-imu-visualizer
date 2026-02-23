#ifndef IMUSENSOR_H
#define IMUSENSOR_H

#include <string>

class IMUSensor {
public:
    IMUSensor(const std::string& name, int axes);
    ~IMUSensor();

    void setCalibration(int axis, float value);
    float getReading(int axis) const;
    const std::string& getName() const;

private:
    std::string m_name; // stores sensor name
    float* m_calibration; // pointer to array of floats
    int m_axes; // stores how many axes we have

};

#endif // IMUSENSOR_H
