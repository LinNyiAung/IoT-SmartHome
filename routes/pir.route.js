// pir.route.js
import express from "express";
import { getPIRData, setPIRData } from "../controllers/pir.controller.js";

const router = express.Router();

// PIR routes
router.get('/motion', getPIRData);  // For fetching the latest PIR data
router.post('/motion', setPIRData); // For posting new PIR data from ESP8266

export default router;
