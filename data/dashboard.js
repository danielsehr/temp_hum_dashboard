const status = document.getElementById("status");

const socket = new WebSocket(
    `ws://${location.host}/ws`
);

socket.onopen = () =>
{
    status.textContent = "Connected";
};

socket.onclose = () =>
{
    status.textContent = "Disconnected";
};

socket.onmessage = (event) =>
{
    console.log(event.data);
};

document
.getElementById("send")
.addEventListener("click", () =>
{
    socket.send("Hello ESP32");
});