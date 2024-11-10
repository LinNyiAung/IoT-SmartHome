import express from "express";
import { getDhtfanautomationStatus, setDhtfanautomationStatus } from "../controllers/dhtfanautomation.controller.js";

const router = express.Router();

// Automation routes
router.get('/status', getDhtfanautomationStatus); // Get current automation status
router.post('/status', setDhtfanautomationStatus); // Update automation status

export default router;
