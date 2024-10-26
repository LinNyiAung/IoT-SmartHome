import express from "express";
import { getLEDStatus, setLEDStatus } from "../controllers/led.controller.js";

const router = express.Router();

// LED routes
router.get('/status', getLEDStatus); // Get LED status
router.post('/status', setLEDStatus); // Set LED status

export default router;
