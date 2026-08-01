const RING_BUFFER_SIZE = 60;

// Chart
const ctx = 
    document
        .getElementById("chart")
        .getContext("2d");

const chart = new Chart(ctx, {
    type: "line",

    data: {
        labels: [],
        datasets: [{
            label: "Temperature",

            data: []
        }]
    },

    options: {
        animation: false,

        responsive: true
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

        // Live values
        temperature.textContent = 
            `${message.data.temperature.toFixed(1)} °C`;

        humidity.textContent =
            `${message.data.humidity.toFixed(1)} %`;

        // Chart
        chart.data.labels.push(
            new Date().toLocaleTimeString()
        );

        chart.data.datasets[0].data.push(
            message.data.temperature
        );

        if (chart.data.labels.length > RING_BUFFER_SIZE){
            chart.data.labels.shift();
            
            chart.data.datasets[0].data.shift();
        }

        chart.update();
    }
};