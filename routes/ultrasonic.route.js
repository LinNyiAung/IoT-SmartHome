import express from "express";
import { getUltrasonicData, setUltrasonicData } from "../controllers/ultrasonic.controller.js";

const router = express.Router();

// Ultrasonic routes
router.get('/distance', getUltrasonicData); // For fetching the latest Ultrasonic sensor data
router.post('/distance', setUltrasonicData); // For posting new Ultrasonic sensor data from ESP8266

export default router;
