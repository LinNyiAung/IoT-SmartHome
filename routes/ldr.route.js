import express from "express";
import { getLDRData, setLDRData } from "../controllers/ldr.controller.js";

const router = express.Router();

// LDR routes
router.get('/light', getLDRData);  // For fetching the latest LDR data
router.post('/light', setLDRData); // For posting new LDR data from ESP8266

export default router;
