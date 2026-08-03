const RING_BUFFER_SIZE = 864;

// Chart
const ctx = 
    document
        .getElementById("chart")
        .getContext("2d");

const chart = new Chart(ctx, {
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

// Rest
const status = document.getElementById("status");
const temperature = document.getElementById("temperature");
const humidity = document.getElementById("humidity");

const socket = new WebSocket(
    `ws://${location.host}/ws`
);


socket.onopen = () => {
    status.textContent = "Connected";
};

socket.onclose = () => {
    status.textContent = "Disconnected";
};


socket.onmessage = (event) => {
    const message = JSON.parse(event.data);

    if (message.type === "sensor"){

        updateLiveValues(message);

        updateChart(message);
    }
};


function updateLiveValues(message){
    temperature.textContent = 
        `${message.data.temperature.toFixed(1)} °C`;

    humidity.textContent =
        `${message.data.humidity.toFixed(1)} %`;
}

function updateChart(message){
    chart.data.labels.push(
            new Date().toLocaleTimeString()
        );

        chart.data.datasets[0].data.push(
            message.data.temperature
        );

        chart.data.datasets[1].data.push(
            message.data.humidity
        );

        if (chart.data.labels.length > RING_BUFFER_SIZE){
            chart.data.labels.shift();
            
            chart.data.datasets[0].data.shift();
            chart.data.datasets[1].data.shift();
        }

        chart.update();
}