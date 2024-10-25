import express from "express";
import { getLEDStatus, setLEDStatus } from "../controllers/sensor.controller.js";

const router = express.Router();

router.get('/status', getLEDStatus);
router.post('/status', setLEDStatus);

export default router;
