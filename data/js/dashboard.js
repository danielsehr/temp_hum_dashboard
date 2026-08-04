import { CurrentMeasurements } from "./ui/live-values.js";
import { ChartManager } from "./ui/chart-manager.js";

const currentMeasurements = new CurrentMeasurements();
const chartManager = new ChartManager();

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

        currentMeasurements.updateCurrentMeasurement(message.data);

        chartManager.addMeasurement(message.data);
    }
};