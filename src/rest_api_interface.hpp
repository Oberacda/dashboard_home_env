//
// Created by david on 4/30/2020.
//

#ifndef HOME_ENV_IOT_DASHBOARD_REST_API_INTERFACE_HPP
#define HOME_ENV_IOT_DASHBOARD_REST_API_INTERFACE_HPP

#include <cpprest/http_client.h>

#include "environemental_data.hpp"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

/*!
 * @brief Endpoints for REST API calls.
 *
 * @details These are used to get the data from the the server.
 * These endpoints have to allow a REST calls.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 */
class rest_api_endpoints {
    std::string client_url;
    std::string temperature_endpoint;
    std::string humidity_endpoint;
    std::string pressure_endpoint;
    std::string illuminance_endpoint;
    std::string uv_endpoint;
public:
    /*!
     * Returns the server url without a specific endpoint.
     *
     * @return The server address.
     */
    [[nodiscard]] const std::string &getClientUrl() const;

    /*!
     * Returns the endpoint for the temperature data.
     *
     * @return The temperature data endpoint.
     */
    [[nodiscard]] const std::string &getTemperatureEndpoint() const;

    /*!
     * Returns the endpoint for the humidity data.
     *
     * @return The humidity data endpoint.
     */
    [[nodiscard]] const std::string &getHumidityEndpoint() const;

    /*!
     * Returns the endpoint for the pressure data.
     *
     * @return The pressure data endpoint.
     */
    [[nodiscard]] const std::string &getPressureEndpoint() const;

    /*!
     * Returns the endpoint for the illumiance data.
     *
     * @return The illumiance data endpoint.
     */
    [[nodiscard]] const std::string &getIlluminanceEndpoint() const;

    /*!
     * Returns the endpoint for the uv data.
     *
     * @return The uv data endpoint.
     */
    [[nodiscard]] const std::string &getUvEndpoint() const;

    rest_api_endpoints(std::string clientUrl, std::string temperatureEndpoint,
                       std::string humidityEndpoint, std::string pressureEndpoint,
                       std::string illuminanceEndpoint, std::string uvEndpoint);
};


/*!
 * @brief REST API interface class that allows to execute a REST call.
 *
 * @details This class provides a wrapper for the REST API calls.
 * This allows the execute the tasks without knowing of the actual API.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 */
class rest_api_interface {

private:
    std::unique_ptr<http_client> http_client_ptr;

    std::unique_ptr<uri_builder> temperature_builder_ptr;
    std::unique_ptr<uri_builder> humidity_builder_ptr;
    std::unique_ptr<uri_builder> pressure_builder_ptr;
    std::unique_ptr<uri_builder> illuminance_builder_ptr;
    std::unique_ptr<uri_builder> uv_builder_ptr;


public:
    /*!
     * Creates a new instance from a set of endpoints for rest calls.
     *
     * @param endpoints The endpoints to connect to for different functions.
     */
    explicit rest_api_interface(const rest_api_endpoints &endpoints);

    /*!
     * Getter of the temperature data from the server.
     * @details This function executes a remote call to the REST API.
     * This used the endpoint {@code rest_api_endpoints::getTemperatureEndpoint()}.
     * @return Vector of environmental data where the data are temperature values.
     */
    std::vector<EnvironmentalData> getTemperatureData() noexcept(false);

    /*!
     * Getter of the pressure data from the server.
     * @details This function executes a remote call to the REST API.
     * This used the endpoint {@code rest_api_endpoints::getPressureEndpoint()}.
     * @return Vector of environmental data where the data are pressure values.
     */
    std::vector<EnvironmentalData> getPressureData() noexcept(false);

    /*!
     * Getter of the humidity data from the server.
     * @details This function executes a remote call to the REST API.
     * This used the endpoint {@code rest_api_endpoints::getHumidityEndpoint()}.
     * @return Vector of environmental data where the data are humidity values.
     */
    std::vector<EnvironmentalData> getHumidityData() noexcept(false);

    /*!
     * Getter of the illuminance data from the server.
     * @details This function executes a remote call to the REST API.
     * This used the endpoint {@code rest_api_endpoints::getIlluminanceEndpoint()}.
     * @return Vector of environmental data where the data are illuminance values.
     */
    std::vector<EnvironmentalData> getIlluminanceData() noexcept(false);

    /*!
     * Getter of the uva data from the server.
     * @details This function executes a remote call to the REST API.
     * This used the endpoint {@code rest_api_endpoints::getUvEndpoint()}.
     * @return Vector of environmental data where the data are uva values.
     */
    std::vector<EnvironmentalData> getUvaData() noexcept(false);

    /*!
     * Getter of the uvb data from the server.
     * @details This function executes a remote call to the REST API.
     * This used the endpoint {@code rest_api_endpoints::getUvEndpoint()}.
     * @return Vector of environmental data where the data are uvb values.
     */
    std::vector<EnvironmentalData> getUvbData() noexcept(false);

    /*!
     * Getter of the uv index data from the server.
     * @details This function executes a remote call to the REST API.
     * This used the endpoint {@code rest_api_endpoints::getUvEndpoint()}.
     * @return Vector of environmental data where the data are uv index values.
     */
    std::vector<EnvironmentalData> getUvIndexData() noexcept(false);
};


#endif //HOME_ENV_IOT_DASHBOARD_REST_API_INTERFACE_HPP
