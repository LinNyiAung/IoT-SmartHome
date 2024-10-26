import DHT from "../models/dht.model.js";

// Controller function to get DHT11 data
export const getDHTData = async (req, res) => {
  try {
    const dhtData = await DHT.findOne().sort({ createdAt: -1 }); // Get latest data
    res.send(dhtData || { temperature: 0, humidity: 0 });
  } catch (error) {
    res.status(500).send({ message: "Error fetching DHT11 data" });
  }
};

// Controller function to set DHT11 data
export const setDHTData = async (req, res) => {
  try {
    const { temperature, humidity } = req.body;
    const updatedDHTData = await DHT.findOneAndUpdate(
      {},
      { temperature, humidity },
      { new: true, upsert: true } // Upsert: update if exists, insert if not
    );
    res.send({ message: "DHT11 data updated", temperature: updatedDHTData.temperature, humidity: updatedDHTData.humidity });
  } catch (error) {
    res.status(500).send({ message: "Error updating DHT11 data" });
  }
};
