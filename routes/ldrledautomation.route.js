import express from "express";
import { getLdrledautomationStatus, setLdrledautomationStatus } from "../controllers/ldrledautomation.controller.js";

const router = express.Router();

// Automation routes
router.get('/status', getLdrledautomationStatus); // Get current automation status
router.post('/status', setLdrledautomationStatus); // Update automation status

export default router;
