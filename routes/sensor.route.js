import express from "express";
import { getLEDStatus, setLEDStatus, getDHTData, setDHTData } from "../controllers/sensor.controller.js";

const router = express.Router();

// LED routes
router.get('/status', getLEDStatus);
router.post('/status', setLEDStatus);

// DHT routes
router.get('/dhtdata', getDHTData); // For fetching the latest DHT data
router.post('/dhtdata', setDHTData); // For posting new DHT data from ESP8266

export default router;