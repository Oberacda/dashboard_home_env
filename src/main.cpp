#include <iostream>

#include <QApplication>
#include <QPushButton>
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <QMainWindow>

#include "rest_api_interface.hpp"
#include "environemental_data.hpp"
#include "ogl_widget.hpp"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

int main(int argc, char* argv[]) {
    QApplication app (argc, argv);


    rest_api_endpoints endpoints("https://api.d4ve.me",
            "/env/temperature",
            "/env/humidity",
            "/env/pressure",
            "/env/illuminance",
            "/env/uv");

    rest_api_interface rest_connection(endpoints);

    auto *temperatureSeries = new QLineSeries();
    auto tempDate = rest_connection.getTemperatureData();
    for (const auto& item: tempDate) {
        temperatureSeries->append(item.getTimestamp().toMSecsSinceEpoch(), item.getData());
    }

    auto *tabWidget = new QTabWidget();

    auto *temperatureChart = new QChart();
    temperatureChart->addSeries(temperatureSeries);
    temperatureChart->legend()->hide();
    temperatureChart->setTitle("Temperature");

    auto *temperatureAxisX = new QDateTimeAxis;
    temperatureAxisX->setTickCount(10);
    temperatureAxisX->setFormat("yyyy-MM-dd hh:mm");
    temperatureAxisX->setTitleText("Date");
    temperatureChart->addAxis(temperatureAxisX, Qt::AlignBottom);
    temperatureSeries->attachAxis(temperatureAxisX);

    auto *temperatureAxisY = new QValueAxis;
    temperatureAxisY->setLabelFormat("%f");
    temperatureAxisY->setTitleText("°C");
    temperatureChart->addAxis(temperatureAxisY, Qt::AlignLeft);
    temperatureSeries->attachAxis(temperatureAxisY);

    auto *temperatureChartView = new QChartView(temperatureChart);
    temperatureChartView->setRenderHint(QPainter::Antialiasing);

    tabWidget->addTab(temperatureChartView, QString::fromStdString(std::string("Temperature")));

    auto *pressureSeries = new QLineSeries();
    auto pressureDate = rest_connection.getPressureData();
    for (const auto& item: pressureDate) {
        pressureSeries->append(item.getTimestamp().toMSecsSinceEpoch(), item.getData());
    }

    auto *pressureChart = new QChart();
    pressureChart->addSeries(pressureSeries);
    pressureChart->legend()->hide();
    pressureChart->setTitle("Pressure");

    auto *pressureAxisX = new QDateTimeAxis;
    pressureAxisX->setTickCount(10);
    pressureAxisX->setFormat("yyyy-MM-dd hh:mm");
    pressureAxisX->setTitleText("Date");
    pressureChart->addAxis(pressureAxisX, Qt::AlignBottom);
    pressureSeries->attachAxis(pressureAxisX);

    auto *pressureAxisY = new QValueAxis;
    pressureAxisY->setLabelFormat("%f");
    pressureAxisY->setTitleText("kPa");
    pressureChart->addAxis(pressureAxisY, Qt::AlignLeft);
    pressureSeries->attachAxis(pressureAxisY);

    auto *pressureChartView = new QChartView(pressureChart);
    pressureChartView->setRenderHint(QPainter::Antialiasing);

    tabWidget->addTab(pressureChartView, QString::fromStdString(std::string("Pressure")));

    auto *humiditySeries = new QLineSeries();
    auto humidityDate = rest_connection.getHumidityData();
    for (const auto& item: humidityDate) {
        humiditySeries->append(item.getTimestamp().toMSecsSinceEpoch(), item.getData());
    }

    auto *humidityChart = new QChart();
    humidityChart->addSeries(humiditySeries);
    humidityChart->legend()->hide();
    humidityChart->setTitle("Humidity");

    auto *humidityAxisX = new QDateTimeAxis;
    humidityAxisX->setTickCount(10);
    humidityAxisX->setFormat("yyyy-MM-dd hh:mm");
    humidityAxisX->setTitleText("Date");
    humidityChart->addAxis(humidityAxisX, Qt::AlignBottom);
    humiditySeries->attachAxis(humidityAxisX);

    auto *humidityAxisY = new QValueAxis;
    humidityAxisY->setLabelFormat("%f");
    humidityAxisY->setTitleText("kPa");
    humidityChart->addAxis(humidityAxisY, Qt::AlignLeft);
    humiditySeries->attachAxis(humidityAxisY);

    auto *humidityChartView = new QChartView(humidityChart);
    humidityChartView->setRenderHint(QPainter::Antialiasing);

    tabWidget->addTab(humidityChartView, QString::fromStdString(std::string("Humidity")));

    auto *uvaSeries = new QLineSeries();
    auto uvaData = rest_connection.getUvaData();
    for (const auto& item: uvaData) {
        uvaSeries->append(item.getTimestamp().toMSecsSinceEpoch(), item.getData());
    }

    auto *uvbSeries = new QLineSeries();
    auto uvbData = rest_connection.getUvbData();
    for (const auto& item: uvbData) {
        uvbSeries->append(item.getTimestamp().toMSecsSinceEpoch(), item.getData());
    }

    auto *uvIndexSeries = new QLineSeries();
    auto uvIndexData = rest_connection.getUvIndexData();
    for (const auto& item: uvIndexData) {
        uvIndexSeries->append(item.getTimestamp().toMSecsSinceEpoch(), item.getData());
    }

    auto *uvChart = new QChart();
    uvChart->addSeries(uvaSeries);
    uvChart->addSeries(uvbSeries);
    uvChart->addSeries(uvIndexSeries);
    uvChart->legend()->hide();
    uvChart->setTitle("UV");

    auto *uvAxisX = new QDateTimeAxis;
    uvAxisX->setTickCount(10);
    uvAxisX->setFormat("yyyy-MM-dd hh:mm");
    uvAxisX->setTitleText("Date");
    uvChart->addAxis(uvAxisX, Qt::AlignBottom);
    uvaSeries->attachAxis(uvAxisX);
    uvbSeries->attachAxis(uvAxisX);

    auto *uvAxisY = new QValueAxis;
    uvAxisY->setLabelFormat("%f");
    uvAxisY->setTitleText("UV");
    uvChart->addAxis(uvAxisY, Qt::AlignLeft);
    uvaSeries->attachAxis(uvAxisY);
    uvbSeries->attachAxis(uvAxisY);

    auto *uvIndexAxisY = new QValueAxis;
    uvIndexAxisY->setLabelFormat("%f");
    uvIndexAxisY->setTitleText("UvIndex");
    uvChart->addAxis(uvIndexAxisY, Qt::AlignRight);
    uvIndexSeries->attachAxis(uvIndexAxisY);

    auto *uvChartView = new QChartView(uvChart);
    uvChartView->setRenderHint(QPainter::Antialiasing);

    tabWidget->addTab(uvChartView, QString::fromStdString(std::string("UV")));

    auto *openGlWidget = new OGLWidget ();
    tabWidget->addTab(openGlWidget, QString::fromStdString(std::string("OpenGl")));

    auto  *boxHorizonalLayout = new QHBoxLayout ();
    boxHorizonalLayout->addWidget(tabWidget);

    QWidget window;
    window.setLayout(boxHorizonalLayout);
    window.setMinimumSize(500, 500);
    window.show();

    return QApplication::exec();
}
