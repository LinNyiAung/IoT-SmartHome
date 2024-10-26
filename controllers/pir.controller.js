// pir.controller.js
import PIR from "../models/pir.model.js";

// Get the current motion detection status
export const getPIRData = async (req, res) => {
  try {
    const pirData = await PIR.findOne().sort({ createdAt: -1 }); // Get latest data
    res.send(pirData || { motionDetected: false });
  } catch (error) {
    res.status(500).send({ message: "Error fetching PIR data" });
  }
};

// Update the motion detection status
export const setPIRData = async (req, res) => {
  try {
    const { motionDetected } = req.body;
    const updatedPIRData = await PIR.findOneAndUpdate(
      {},
      { motionDetected },
      { new: true, upsert: true }
    );
    res.send({ message: "PIR data updated", motionDetected: updatedPIRData.motionDetected });
  } catch (error) {
    res.status(500).send({ message: "Error updating PIR data" });
  }
};
