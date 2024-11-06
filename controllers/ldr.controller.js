import LDR from "../models/ldr.model.js";

// Controller function to get the latest LDR data
export const getLDRData = async (req, res) => {
  try {
    const ldrData = await LDR.findOne().sort({ createdAt: -1 }); // Get latest data
    res.send(ldrData || { lightIntensity: false });
  } catch (error) {
    res.status(500).send({ message: "Error fetching LDR data" });
  }
};

// Controller function to set LDR data
export const setLDRData = async (req, res) => {
  try {
    const { lightIntensity } = req.body;
    const updatedLDRData = await LDR.findOneAndUpdate(
      {},
      { lightIntensity },
      { new: true, upsert: true } // Upsert: update if exists, insert if not
    );
    res.send({ message: "LDR data updated", lightIntensity: updatedLDRData.lightIntensity });
  } catch (error) {
    res.status(500).send({ message: "Error updating LDR data" });
  }
};
