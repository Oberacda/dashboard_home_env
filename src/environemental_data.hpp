//
// Created by david on 4/30/2020.
//

#ifndef HOME_ENV_IOT_DASHBOARD_ENVIRONMENTAL_DATA_HPP
#define HOME_ENV_IOT_DASHBOARD_ENVIRONMENTAL_DATA_HPP


#include <memory>
#include <vector>
#include <QtCore/qdatetime.h>

class EnvironmentalData {

private:
   QDateTime timestamp;
   double data;

public:
    EnvironmentalData(QDateTime timestamp, double data);

    [[nodiscard]] const QDateTime &getTimestamp() const;

    void setTimestamp(const QDateTime &timestamp);

    [[nodiscard]] double getData() const;

    void setData(double data);

};


#endif //HOME_ENV_IOT_DASHBOARD_ENVIRONMENTAL_DATA_HPP
