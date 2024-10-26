import LED from "../models/led.model.js";

// Controller function to get LED status
export const getLEDStatus = async (req, res) => {
  try {
    const led = await LED.findOne();
    res.send(led ? led.status : 'OFF'); // Default to 'OFF' if no status found
  } catch (error) {
    res.status(500).send({ message: "Error fetching LED status" });
  }
};

// Controller function to set LED status
export const setLEDStatus = async (req, res) => {
  try {
    const { status } = req.body;
    let led = await LED.findOne();
    if (led) {
      led.status = status;
    } else {
      led = new LED({ status });
    }
    await led.save();
    res.send({ message: 'LED status updated', status });
  } catch (error) {
    res.status(500).send({ message: "Error updating LED status" });
  }
};
