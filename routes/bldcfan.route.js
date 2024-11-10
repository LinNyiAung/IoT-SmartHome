import express from "express";
import { getBLDCFANStatus, setBLDCFANStatus } from "../controllers/bldcfan.controller.js";

const router = express.Router();

// BLDC Fan routes
router.get('/bldcfanstatus', getBLDCFANStatus); // Get BLDC Fan status
router.post('/bldcfanstatus', setBLDCFANStatus); // Set BLDC Fan status

export default router;
