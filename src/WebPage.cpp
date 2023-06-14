#include "WebPage.h"

WebPage::WebPage(SensorReadings* readings) : readings(readings) {}

String WebPage::getHTML() {
    String html = R"(
    <!DOCTYPE html>
    <html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" rel="stylesheet">
        <script src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js"></script>
        <style>
            body { padding: 20px; }
            .sensor { font-weight: bold; margin-top: 20px; }
        </style>
    </head>
    <body>
        <div class="container">
            <div class="jumbotron text-center">
                <h2 class="display-4">Weather Live</h2>
                <a class="btn btn-primary mt-4" href="https://r5nzumpc6j2o6nm7zqzszq.on.drv.tw/Weather-live/">More Weather</a>
            </div>
            <div class="row mt-5">
                <div class="col-md-6 sensor">
                    <div class="card">
                        <div class="card-header text-center">
                            <h3>Soil Moisture</h3>
                        </div>
                        <div class="card-body">
                            <h4 class="value" id="soilValue"></h4>
                            <p class="status" id="soilStatus"></p>
                        </div>
                    </div>
                </div>
                <div class="col-md-6 sensor">
                    <div class="card">
                        <div class="card-header text-center">
                            <h3>Carbon Dioxide</h3>
                        </div>
                        <div class="card-body">
                            <h4 class="value" id="gasValue"></h4>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <script>
            function fetchSensorData() {
                $.getJSON('/soil', function(data) {
                    $('#soilValue').text(data.value);
                    $('#soilStatus').text(data.status);
                });
                $.getJSON('/gas', function(data) {
                    $('#gasValue').text(data.value);
                });
            }
            setInterval(fetchSensorData, 1000); // Fetch every 1 second
        </script>
    </body>
    </html>
    )";
    return html;
}
