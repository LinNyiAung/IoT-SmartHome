import Ultrasonicledautomation from "../models/ultrasonicledautomation.model.js";

// Get automation status
export const getUltrasonicledautomationStatus = async (req, res) => {
  try {
    const ultrasonicledautomation = await Ultrasonicledautomation.findOne();
    res.send({ isActive: ultrasonicledautomation ? ultrasonicledautomation.isActive : true });
  } catch (error) {
    res.status(500).send({ message: "Error fetching automation status" });
  }
};

// Set automation status
export const setUltrasonicledautomationStatus = async (req, res) => {
  try {
    const { isActive } = req.body;
    let ultrasonicledautomation = await Ultrasonicledautomation.findOne();
    if (ultrasonicledautomation) {
        ultrasonicledautomation.isActive = isActive;
    } else {
        ultrasonicledautomation = new Ultrasonicledautomation({ isActive });
    }
    await ultrasonicledautomation.save();
    res.send({ message: "Automation status updated", isActive });
  } catch (error) {
    res.status(500).send({ message: "Error updating automation status" });
  }
};
