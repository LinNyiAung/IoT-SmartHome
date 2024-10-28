import Ultrasonic from "../models/ultrasonic.model.js";

// Get the latest ultrasonic data
export const getUltrasonicData = async (req, res) => {
  try {
    const ultrasonicData = await Ultrasonic.findOne().sort({ createdAt: -1 });
    res.send(ultrasonicData || { distance: 0 });
  } catch (error) {
    res.status(500).send({ message: "Error fetching Ultrasonic sensor data" });
  }
};

// Update the ultrasonic sensor data
export const setUltrasonicData = async (req, res) => {
  try {
    const { distance } = req.body;
    const updatedUltrasonicData = await Ultrasonic.findOneAndUpdate(
      {},
      { distance },
      { new: true, upsert: true }
    );
    res.send({ message: "Ultrasonic sensor data updated", distance: updatedUltrasonicData.distance });
  } catch (error) {
    res.status(500).send({ message: "Error updating Ultrasonic sensor data" });
  }
};
