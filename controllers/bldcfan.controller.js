import BLDCFAN from "../models/bldcfan.model.js";

// Controller function to get BLDC Fan status
export const getBLDCFANStatus = async (req, res) => {
  try {
    const bldcfan = await BLDCFAN.findOne();
    res.send(bldcfan ? bldcfan.status : 'OFF'); // Default to 'OFF' if no status found
  } catch (error) {
    res.status(500).send({ message: "Error fetching BLDCFAN status" });
  }
};

// Controller function to set BLDC Fan status
export const setBLDCFANStatus = async (req, res) => {
  try {
    const { status } = req.body;
    let bldcfan = await BLDCFAN.findOne();
    if (bldcfan) {
        bldcfan.status = status;
    } else {
        bldcfan = new BLDCFAN({ status });
    }
    await bldcfan.save();
    res.send({ message: 'BLDCFAN status updated', status });
  } catch (error) {
    res.status(500).send({ message: "Error updating BLDCFAN status" });
  }
};
