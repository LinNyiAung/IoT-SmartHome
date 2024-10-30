import express from "express";
import http from "http";
import dotenv from "dotenv";
import mongoose from "mongoose";
import cors from "cors";
import { initWebSocketServer } from "./utils/websocket.js"; // WebSocket logic
import ledRoutes from "./routes/led.route.js";
import dhtRoutes from "./routes/dht.route.js";
import pirRoutes from "./routes/pir.route.js";
import ultrasonicRoutes from "./routes/ultrasonic.route.js";
import ldrRoutes from "./routes/ldr.route.js";

dotenv.config();

const app = express();
const server = http.createServer(app); // Create an HTTP server

// Middlewares
app.use(cors());
app.use(express.json());

// Connect to MongoDB Atlas
mongoose.connect(process.env.MONGO)
  .then(() => console.log('Connected to MongoDB Atlas'))
  .catch(err => console.log('MongoDB Atlas connection error:', err));

// Routes
app.use('/api/led', ledRoutes);
app.use('/api/dht', dhtRoutes);
app.use('/api/pir', pirRoutes);
app.use('/api/ultrasonic', ultrasonicRoutes);
app.use('/api/ldr', ldrRoutes);

// Initialize WebSocket server
initWebSocketServer(server);

const PORT = process.env.PORT || 5000;
server.listen(PORT, () => console.log(`Server running on port ${PORT}`));
