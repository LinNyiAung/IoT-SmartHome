import { WebSocketServer } from "ws";
import DHT from "../models/dht.model.js"; // Import DHT model

export const initWebSocketServer = (server) => {
  const wss = new WebSocketServer({ server }); // Create WebSocket server

  wss.on("connection", (ws) => {
    console.log("New WebSocket connection");

    ws.on("close", () => console.log("WebSocket connection closed"));

    // Fetch and send the latest DHT data every 5 seconds
    const interval = setInterval(async () => {
      try {
        const dhtData = await DHT.findOne(); // Retrieve the latest DHT data
        if (dhtData) {
          ws.send(JSON.stringify({
            temperature: dhtData.temperature,
            humidity: dhtData.humidity,
          }));
        }
      } catch (error) {
        console.error("Error broadcasting DHT data:", error);
      }
    }, 5000);

    // Clear the interval when WebSocket is closed
    ws.on("close", () => clearInterval(interval));
  });
};
