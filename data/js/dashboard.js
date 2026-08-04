import { CurrentMeasurements } from "./ui/current-measurements.js";
import { ChartManager } from "./ui/chart-manager.js";
import { WebSocketClient } from "./web/websocket-client.js";

const socket = new WebSocketClient();
const currentMeasurements = new CurrentMeasurements();
const chartManager = new ChartManager();


socket.onopen(() => {
    status.textContent = "Connected";
});

socket.onclose(() => {
    status.textContent = "Disconnected";
});


socket.onMeasurement((measurement) => {
    currentMeasurements.updateCurrentMeasurement(measurement);

    chartManager.addMeasurement(measurement);
});