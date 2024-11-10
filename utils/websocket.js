import { WebSocketServer } from "ws";
import DHT from "../models/dht.model.js"; 
import PIR from "../models/pir.model.js";
import Ultrasonic from "../models/ultrasonic.model.js";
import LDR from "../models/ldr.model.js";
import LED from "../models/led.model.js";
import Current from "../models/current.model.js";

export const initWebSocketServer = (server) => {
  const wss = new WebSocketServer({ server });

  wss.on("connection", (ws) => {
    console.log("New WebSocket connection");

    ws.on("close", () => console.log("WebSocket connection closed"));

    const interval = setInterval(async () => {
      try {
        // Fetch DHT data
        const dhtData = await DHT.findOne();
        const pirData = await PIR.findOne(); 
        const ultrasonicData = await Ultrasonic.findOne();
        const ldrData = await LDR.findOne();
        const ledData = await LED.findOne();
        const currentData = await Current.findOne();

        ws.send(JSON.stringify({
          temperature: dhtData?.temperature || 0,
          humidity: dhtData?.humidity || 0,
          motionDetected: pirData?.motionDetected || false,
          distance: ultrasonicData?.distance || 0,
          lightIntensity: ldrData?.lightIntensity || 0,
          ledStatus: ledData?.status || 'OFF',
          voltage: currentData?.voltage || 0,
          current: currentData?.current || 0
        }));
      } catch (error) {
        console.error("Error broadcasting sensor data:", error);
      }
    }, 5000);

    ws.on("close", () => clearInterval(interval));
  });
};
