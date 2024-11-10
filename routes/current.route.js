import express from "express";
import { getCurrentData, setCurrentData } from "../controllers/current.controller.js";

const router = express.Router();

// DHT routes
router.get('/currentdata', getCurrentData); // For fetching the latest DHT data
router.post('/currentdata', setCurrentData); // For posting new DHT data from ESP8266

export default router;
