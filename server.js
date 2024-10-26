import express from "express";
import http from "http";
import { WebSocketServer } from "ws";
import dotenv from "dotenv";
import mongoose from "mongoose";
import cors from "cors";
import sensorRoutes from "./routes/sensor.route.js";
import DHT from "./models/dht.model.js"; // Import DHT model

dotenv.config();

const app = express();
const server = http.createServer(app); // Create an HTTP server
const wss = new WebSocketServer({ server }); // Create WebSocket server

app.use(cors());
app.use(express.json());

// Connect to MongoDB Atlas
mongoose.connect(process.env.MONGO)
  .then(() => console.log('Connected to MongoDB Atlas'))
  .catch(err => console.log('MongoDB Atlas connection error:', err));

// Routes
app.use('/api/led', sensorRoutes);
app.use('/api/dht', sensorRoutes);

// Broadcast latest DHT data
wss.on("connection", (ws) => {
  console.log("New WebSocket connection");
  
  ws.on("close", () => console.log("WebSocket connection closed"));

  // Fetch and send the latest DHT data every 5 seconds
  setInterval(async () => {
    try {
      const dhtData = await DHT.findOne(); // Retrieve the single DHT data document
      if (dhtData) {
        ws.send(JSON.stringify({
          temperature: dhtData.temperature,
          humidity: dhtData.humidity,
        }));
      }
    } catch (error) {
      console.error("Error broadcasting DHT data:", error);
    }
  }, 5000); // Send every 5 seconds
});

const PORT = 5000;
server.listen(PORT, () => console.log(`Server running on port ${PORT}`));