import Ldrledautomation from "../models/ldrledautomation.model.js";

// Get automation status
export const getLdrledautomationStatus = async (req, res) => {
  try {
    const ldrledautomation = await Ldrledautomation.findOne();
    res.send({ isActive: ldrledautomation ? ldrledautomation.isActive : true });
  } catch (error) {
    res.status(500).send({ message: "Error fetching automation status" });
  }
};

// Set automation status
export const setLdrledautomationStatus = async (req, res) => {
  try {
    const { isActive } = req.body;
    let ldrledautomation = await Ldrledautomation.findOne();
    if (ldrledautomation) {
        ldrledautomation.isActive = isActive;
    } else {
        ldrledautomation = new Ldrledautomation({ isActive });
    }
    await ldrledautomation.save();
    res.send({ message: "Automation status updated", isActive });
  } catch (error) {
    res.status(500).send({ message: "Error updating automation status" });
  }
};
