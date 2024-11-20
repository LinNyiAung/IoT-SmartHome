import express from "express";
import { getUltrasonicledautomationStatus, setUltrasonicledautomationStatus } from "../controllers/ultrasonicledautomation.controller.js";

const router = express.Router();

// Automation routes
router.get('/status', getUltrasonicledautomationStatus); // Get current automation status
router.post('/status', setUltrasonicledautomationStatus); // Update automation status

export default router;
