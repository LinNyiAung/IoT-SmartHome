import express from "express";
import { getCameraStream } from "../controllers/camera.controller.js";

const router = express.Router();

// Route to get camera stream or capture an image
router.get('/stream', getCameraStream);

export default router;
