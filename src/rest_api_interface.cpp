//
// Created by david on 4/30/2020.
//

#include "rest_api_interface.hpp"

#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include <utility>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

rest_api_endpoints::rest_api_endpoints(std::string clientUrl, std::string temperatureEndpoint,
                                       std::string humidityEndpoint, std::string pressureEndpoint,
                                       std::string illuminanceEndpoint, std::string uvEndpoint)
        : client_url(std::move(clientUrl)), temperature_endpoint(std::move(temperatureEndpoint)), humidity_endpoint(std::move(humidityEndpoint)),
          pressure_endpoint(std::move(pressureEndpoint)), illuminance_endpoint(std::move(illuminanceEndpoint)), uv_endpoint(std::move(uvEndpoint)) {}

const std::string &rest_api_endpoints::getClientUrl() const {
    return client_url;
}

const std::string &rest_api_endpoints::getTemperatureEndpoint() const {
    return temperature_endpoint;
}

const std::string &rest_api_endpoints::getHumidityEndpoint() const {
    return humidity_endpoint;
}

const std::string &rest_api_endpoints::getPressureEndpoint() const {
    return pressure_endpoint;
}

const std::string &rest_api_endpoints::getIlluminanceEndpoint() const {
    return illuminance_endpoint;
}

const std::string &rest_api_endpoints::getUvEndpoint() const {
    return uv_endpoint;
}

rest_api_interface::rest_api_interface(const rest_api_endpoints& endpoints) {
    this->http_client_ptr = std::make_unique<http_client>(uri(utility::conversions::to_string_t(endpoints.getClientUrl())));

    this->temperature_builder_ptr =  std::make_unique<uri_builder>(uri(utility::conversions::to_string_t(endpoints.getTemperatureEndpoint())));
    this->humidity_builder_ptr = std::make_unique<uri_builder>(uri(utility::conversions::to_string_t(endpoints.getHumidityEndpoint())));
    this->pressure_builder_ptr = std::make_unique<uri_builder>(uri(utility::conversions::to_string_t(endpoints.getPressureEndpoint())));
    this->illuminance_builder_ptr = std::make_unique<uri_builder>(uri(utility::conversions::to_string_t(endpoints.getIlluminanceEndpoint())));
    this->uv_builder_ptr = std::make_unique<uri_builder>(uri(utility::conversions::to_string_t(endpoints.getUvEndpoint())));
}


std::vector<EnvironmentalData> rest_api_interface::getTemperatureData() noexcept(false){
    std::vector<EnvironmentalData> data;

    auto temperatureRequestTask = this->http_client_ptr->request(methods::GET, this->temperature_builder_ptr->to_string())
            .then([=](const http_response& response)
                  {
                      return response.extract_json();
                  });

    auto status = temperatureRequestTask.wait();
    if (status != Concurrency::completed) {
        throw std::runtime_error("REST GET request failed!");
    }

    auto temperatureValueArray = temperatureRequestTask.get();

    for (auto value : temperatureValueArray.as_array()) {
        QString timestampString = QString::fromStdString(utility::conversions::to_utf8string(value[U("timestamp")].as_string()));

        auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
        auto temperatureValue = value[U("temperature")].as_double();
        data.emplace_back(timestamp, temperatureValue);
    }

    return data;
}

std::vector<EnvironmentalData> rest_api_interface::getPressureData() noexcept(false) {
    std::vector<EnvironmentalData> data;

    auto pressureRequestTask = this->http_client_ptr->request(methods::GET, this->pressure_builder_ptr->to_string())
            .then([=](const http_response& response)
                  {
                      return response.extract_json();
                  });
    auto status = pressureRequestTask.wait();
    if (status != Concurrency::completed) {
        throw std::runtime_error("REST GET request failed!");
    }

    auto pressureValueArray = pressureRequestTask.get();

    for (auto value : pressureValueArray.as_array()) {
        QString timestampString = QString::fromStdString(utility::conversions::to_utf8string(value[U("timestamp")].as_string()));

        auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
        auto pressureValue = value[U("pressure")].as_double();
        data.emplace_back(timestamp, pressureValue);
    }

    return data;
}

std::vector<EnvironmentalData> rest_api_interface::getHumidityData() noexcept(false){
    std::vector<EnvironmentalData> data;

    auto humidityRequestTask = this->http_client_ptr->request(methods::GET, this->humidity_builder_ptr->to_string())
            .then([=](const http_response& response)
                  {
                      return response.extract_json();
                  });

    auto status = humidityRequestTask.wait();
    if (status != Concurrency::completed) {
        throw std::runtime_error("REST GET request failed!");
    }
    auto humidityValueArray = humidityRequestTask.get();

    for (auto value : humidityValueArray.as_array()) {
        QString timestampString = QString::fromStdString(utility::conversions::to_utf8string(value[U("timestamp")].as_string()));

        auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
        auto humidityValue = value[U("humidity")].as_double();
        data.emplace_back(timestamp, humidityValue);
    }

    return data;
}

std::vector<EnvironmentalData> rest_api_interface::getIlluminanceData() noexcept(false){
    std::vector<EnvironmentalData> data;

    auto illumianceRequestTask = this->http_client_ptr->request(methods::GET, this->illuminance_builder_ptr->to_string())
            .then([=](const http_response& response)
                  {
                      return response.extract_json();
                  });

    auto status = illumianceRequestTask.wait();
    if (status != Concurrency::completed) {
        throw std::runtime_error("REST GET request failed!");
    }

    for (auto value : illumianceRequestTask.get().as_array()) {
        QString timestampString = QString::fromStdString(utility::conversions::to_utf8string(value[U("timestamp")].as_string()));

        auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
        auto illuminanceValue = value[U("illumiance")].as_double();
        data.emplace_back(timestamp, illuminanceValue);
    }

    return data;
}

std::vector<EnvironmentalData> rest_api_interface::getUvaData() noexcept(false){
    std::vector<EnvironmentalData> data;

    auto uvRequestTask = this->http_client_ptr->request(methods::GET, this->uv_builder_ptr->to_string())
            .then([=](const http_response& response)
                  {
                      return response.extract_json();
                  });

    uvRequestTask.wait();
    auto uvJsonData = uvRequestTask.get();

    for (auto value : uvJsonData.as_array()) {
        QString timestampString = QString::fromStdString(utility::conversions::to_utf8string(value[U("timestamp")].as_string()));

        auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
        auto uvaValue = value[U("uva")].as_double();
        data.emplace_back(timestamp, uvaValue);
    }

    return data;
}

std::vector<EnvironmentalData> rest_api_interface::getUvbData() noexcept(false){
    std::vector<EnvironmentalData> data;

    auto uvRequestTask = this->http_client_ptr->request(methods::GET, this->uv_builder_ptr->to_string())
            .then([=](const http_response& response)
                  {
                      return response.extract_json();
                  });
    auto status = uvRequestTask.wait();
    if (status != Concurrency::completed) {
        throw std::runtime_error("REST GET request failed!");
    }
    auto uvJsonData = uvRequestTask.get();

    for (auto value : uvJsonData.as_array()) {
        QString timestampString = QString::fromStdString(utility::conversions::to_utf8string(value[U("timestamp")].as_string()));

        auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
        auto uvbValue = value[U("uvb")].as_double();
        data.emplace_back(timestamp, uvbValue);
    }

    return data;
}

std::vector<EnvironmentalData> rest_api_interface::getUvIndexData() noexcept(false){
    std::vector<EnvironmentalData> data;

    auto uvRequestTask = this->http_client_ptr->request(methods::GET, this->uv_builder_ptr->to_string())
            .then([=](const http_response& response)
                  {
                      return response.extract_json();
                  });
    auto status = uvRequestTask.wait();
    if (status != Concurrency::completed) {
        throw std::runtime_error("REST GET request failed!");
    }

    auto uvJsonData = uvRequestTask.get();

    for (auto value : uvJsonData.as_array()) {
        QString timestampString = QString::fromStdString(utility::conversions::to_utf8string(value[U("timestamp")].as_string()));

        auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
        auto uvIndexValue = value[U("uvIndex")].as_double();
        data.emplace_back(timestamp, uvIndexValue);
    }

    return data;
}

