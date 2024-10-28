import { WebSocketServer } from "ws";
import DHT from "../models/dht.model.js"; // Import DHT model
import PIR from "../models/pir.model.js";
import Ultrasonic from "../models/ultrasonic.model.js";

export const initWebSocketServer = (server) => {
  const wss = new WebSocketServer({ server });

  wss.on("connection", (ws) => {
    console.log("New WebSocket connection");

    ws.on("close", () => console.log("WebSocket connection closed"));

    const interval = setInterval(async () => {
      try {
        // Fetch DHT data
        const dhtData = await DHT.findOne();
        const pirData = await PIR.findOne(); // Fetch PIR data
        const ultrasonicData = await Ultrasonic.findOne();

        ws.send(JSON.stringify({
          temperature: dhtData?.temperature || 0,
          humidity: dhtData?.humidity || 0,
          motionDetected: pirData?.motionDetected || false,
          distance: ultrasonicData?.distance || 0,
        }));
      } catch (error) {
        console.error("Error broadcasting sensor data:", error);
      }
    }, 5000);

    ws.on("close", () => clearInterval(interval));
  });
};
