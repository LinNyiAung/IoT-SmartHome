import Dhtfanautomation from "../models/dhtfanautomation.model.js";

// Get automation status
export const getDhtfanautomationStatus = async (req, res) => {
  try {
    const dhtfanautomation = await Dhtfanautomation.findOne();
    res.send({ isActive: dhtfanautomation ? dhtfanautomation.isActive : true });
  } catch (error) {
    res.status(500).send({ message: "Error fetching automation status" });
  }
};

// Set automation status
export const setDhtfanautomationStatus = async (req, res) => {
  try {
    const { isActive } = req.body;
    let dhtfanautomation = await Dhtfanautomation.findOne();
    if (dhtfanautomation) {
        dhtfanautomation.isActive = isActive;
    } else {
        dhtfanautomation = new Dhtfanautomation({ isActive });
    }
    await dhtfanautomation.save();
    res.send({ message: "Automation status updated", isActive });
  } catch (error) {
    res.status(500).send({ message: "Error updating automation status" });
  }
};
