import { ChartManager } from "./ui/chart-manager.js";

const chartManager = new ChartManager();

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

        chartManager.addMeasurement(message.data);
    }
};


function updateLiveValues(message){
    temperature.textContent = 
        `${message.data.temperature.toFixed(1)} °C`;

    humidity.textContent =
        `${message.data.humidity.toFixed(1)} %`;
}