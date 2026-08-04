export class ChartManager {
    static BUFFER_SIZE = 864;

    constructor() {
        this.ctx =
            document
                .getElementById("chart")
                .getContext("2d");

        this.chart = new Chart(this.ctx, {
            type: "line",

            data: {
                labels: [],
                datasets: [
                    {
                        label: "Temperature",
                        data: [],
                        yAxisID: "temperature",

                        borderColor: "#e53935",
                        backgroundColor: "#e53935",
                    },
                    {
                        label: "Humidity",
                        data: [],
                        yAxisID: "humidity",

                        borderColor: "#1e88e5",
                        backgroundColor: "#1e88e5",
                    }
                ]
            },

            options: {
                animation: false,
                responsive: true,

                scales: {
                    temperature: {
                        type: "linear",
                        position: "left",

                        min: 0,
                        max: 50,
                    },
                    humidity: {
                        type: "linear",
                        position: "right",

                        min: 0,
                        max: 100,

                        grid: {
                            drawOnChartArea: false
                        }
                    }
                }
            }
        });
    }


    #createTimestamp() {
        return new Date().toLocaleTimeString();
    }

    #appendMeasurement(data) {
        this.chart.data.labels.push(this.#createTimestamp());
        this.chart.data.datasets[0].data.push(data.temperature);
        this.chart.data.datasets[1].data.push(data.humidity);
    }

    #trimBuffer() {
        if (this.chart.data.labels.length > ChartManager.BUFFER_SIZE) {
            this.chart.data.labels.shift();

            this.chart.data.datasets[0].data.shift();
            this.chart.data.datasets[1].data.shift();
        }
    }

    addMeasurement(data) {
        this.#appendMeasurement(data);
        this.#trimBuffer();
        this.chart.update();
    }
}