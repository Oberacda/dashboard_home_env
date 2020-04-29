#include <iostream>

#include <QApplication>
#include <QPushButton>
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <QMainWindow>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

int main(int argc, char* argv[]) {
    auto fileStream = std::make_shared<ostream>();
    utility::stringstream_t ss1;

    // Create http_client to send the request.
    http_client client(U("https://api.d4ve.me"));

    // Build request URI and start the request.
    uri_builder builder(U("/env/pressure"));
    //builder.append_query(U("q"), U("cpprestsdk github"));
    auto requestTask = client.request(methods::GET, builder.to_string())
            .then([=](http_response response)
                  {
                      printf("Received response status code:%u\n", response.status_code());

                      // Write response body into the file.


                      return response.extract_json();
                  });


    QLineSeries *series = new QLineSeries();
    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        requestTask.wait();
        web::json::value requestValue = requestTask.get();

        QString format = "yyyy-MM-ddThh:mm:ss";
        for (auto value : requestValue.as_array()) {

            QString timestampString = QString::fromStdString(value["timestamp"].as_string());
            std::cout << timestampString.toStdString() << std::endl;

            auto timestamp = QDateTime::fromString(timestampString, Qt::ISODate);
            auto pressureValue = value["pressure"].as_double();

            if (pressureValue > 90.0)
                series->append(timestamp.toMSecsSinceEpoch(), pressureValue);
        }
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }

    QApplication app (argc, argv);



    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Pressure");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("yyyy-MM-dd hh:mm");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%f");
    axisY->setTitleText("kPa");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return app.exec();
}
