//
// Created by david on 4/30/2020.
//

#include "environemental_data.hpp"

#include <utility>

EnvironmentalData::EnvironmentalData(QDateTime timestamp, double data) : timestamp(std::move(timestamp)), data(data) {}

const QDateTime &EnvironmentalData::getTimestamp() const {
    return timestamp;
}

void EnvironmentalData::setTimestamp(const QDateTime &timestamp) {
    EnvironmentalData::timestamp = timestamp;
}

double EnvironmentalData::getData() const {
    return data;
}

void EnvironmentalData::setData(double data) {
    EnvironmentalData::data = data;
}
