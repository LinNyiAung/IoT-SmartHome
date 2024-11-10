import Current from "../models/current.model.js";

// Controller function to get Current data
export const getCurrentData = async (req, res) => {
  try {
    const currentData = await Current.findOne().sort({ createdAt: -1 }); // Get latest data
    res.send(currentData || { voltage: 0, current: 0 });
  } catch (error) {
    res.status(500).send({ message: "Error fetching Current data" });
  }
};

// Controller function to set Current data
export const setCurrentData = async (req, res) => {
  try {
    const { voltage, current } = req.body;
    const updatedCurrentData = await Current.findOneAndUpdate(
      {},
      { voltage, current },
      { new: true, upsert: true } // Upsert: update if exists, insert if not
    );
    res.send({ message: "Current data updated", voltage: updatedCurrentData.voltage, current: updatedCurrentData.current });
  } catch (error) {
    res.status(500).send({ message: "Error updating Current data" });
  }
};
