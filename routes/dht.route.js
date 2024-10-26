import express from "express";
import { getDHTData, setDHTData } from "../controllers/dht.controller.js";

const router = express.Router();

// DHT routes
router.get('/dhtdata', getDHTData); // For fetching the latest DHT data
router.post('/dhtdata', setDHTData); // For posting new DHT data from ESP8266

export default router;
