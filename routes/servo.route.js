import express from "express";
import { getServoAngle, setServoAngle } from "../controllers/servo.controller.js";

const router = express.Router();

// Servo routes
router.get('/angle', getServoAngle); // Get servo angle
router.post('/angle', setServoAngle); // Set servo angle

export default router;
