#include "IMUSensor.h"

IMUSensor::IMUSensor(const std::string& name, int axes)
    : m_name(name), m_axes(axes)
{
    m_calibration = new float[m_axes]{0.0f};
}

IMUSensor::~IMUSensor()
{
    delete[] m_calibration;
}

void IMUSensor::setCalibration(int axis, float value)
{
    if (axis >= 0 && axis < m_axes)
        m_calibration[axis] = value;
}

float IMUSensor::getReading(int axis) const
{
    if (axis >= 0 && axis < m_axes)
        return m_calibration[axis];

    return 0.0f;
}

const std::string& IMUSensor::getName() const
{
    return m_name;
}

