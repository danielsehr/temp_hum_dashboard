export class CurrentMeasurements {
    constructor() {
        const status = document.getElementById("status");
        const temperature = document.getElementById("temperature");
        const humidity = document.getElementById("humidity");
    }
    
    updateCurrentMeasurement(data){
        temperature.textContent = `${data.temperature.toFixed(1)} °C`;
        humidity.textContent = `${data.humidity.toFixed(1)} %`;
    }
}