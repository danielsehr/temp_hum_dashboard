import { CurrentMeasurements } from "./ui/current-measurements.js";
import { ChartManager } from "./ui/chart-manager.js";
import { WebSocketClient } from "./web/websocket-client.js";

const socket = new WebSocketClient();

const connectionStatus = document.getElementById("connectionStatus")
const experimentStatus = document.getElementById("experimentStatus")

const currentMeasurements = new CurrentMeasurements();

const startButton = document.getElementById("startExperiment");
const stopButton = document.getElementById("stopExperiment");
const downloadButton = document.getElementById("downloadCsv");

const chartManager = new ChartManager();



socket.onopen(() => {
    connectionStatus.textContent = "Connected";
    connectionStatus.classList.add("connected")
});

socket.onclose(() => {
    connectionStatus.textContent = "Disconnected";
    connectionStatus.classList.remove("connected")
});

initializeExperimentState();

socket.onMeasurement((measurement) => {
    currentMeasurements.updateCurrentMeasurement(measurement);

    chartManager.addMeasurement(measurement);
});


startButton.addEventListener("click", async () => {
    const response = await fetch("/api/experiment/start", {method: "POST"})

    if (!response.ok) {
        console.error("Failed to start experiment");
        return;
    }

    updateExperimentUi(true);
})

stopButton.addEventListener("click", async () => {
    const response = await fetch("/api/experiment/stop", {method: "POST"})

    if (!response.ok) {
        console.error("Failed to stop experiment");
        return;
    }

    updateExperimentUi(false);
})

function updateExperimentUi(recording) {
    startButton.disabled = recording;
    stopButton.disabled = !recording;

    experimentStatus.textContent =
        recording
            ? "Recording"
            : "Not recording";
}

async function initializeExperimentState() {
    const response = await fetch("/api/experiment/status");

    if (!response.ok) {
        console.error(
            "Failed to retrieve experiment status."
        );
        return;
    }

    const state = await response.json();

    updateExperimentUi(state.recording);
}

downloadButton.addEventListener("click", () => {
    const link = document.createElement("a");
    
    // window.location.href = "/api/experiment/download";
    link.href = "/api/experiment/download";
    
    document.body.appendChild(link);
    link.click();
    link.remove();
});