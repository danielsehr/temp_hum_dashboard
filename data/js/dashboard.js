import { CurrentMeasurements } from "./ui/current-measurements.js";
import { ChartManager } from "./ui/chart-manager.js";
import { WebSocketClient } from "./web/websocket-client.js";

const socket = new WebSocketClient();
const currentMeasurements = new CurrentMeasurements();
const chartManager = new ChartManager();
const status = document.getElementById("status")


socket.onopen(() => {
    status.textContent = "Connected";
    status.classList.add("connected")
});

socket.onclose(() => {
    status.textContent = "Disconnected";
    status.classList.remove("connected")
});


socket.onMeasurement((measurement) => {
    currentMeasurements.updateCurrentMeasurement(measurement);

    chartManager.addMeasurement(measurement);
});


document
    .getElementById("downloadCsv")
    .addEventListener("click", () => {
        window.location.href = "/experiments/exp001.csv";
    });