import Servo from "../models/servo.model.js";

// Get Servo angle
export const getServoAngle = async (req, res) => {
  try {
    const servo = await Servo.findOne();
    res.send(servo ? servo.angle.toString() : '0'); // Default to '0' if no angle found
  } catch (error) {
    res.status(500).send({ message: "Error fetching Servo angle" });
  }
};

// Set Servo angle
export const setServoAngle = async (req, res) => {
  try {
    const { angle } = req.body;
    let servo = await Servo.findOne();
    if (servo) {
      servo.angle = angle;
    } else {
      servo = new Servo({ angle });
    }
    await servo.save();
    res.send({ message: 'Servo angle updated', angle });
  } catch (error) {
    res.status(500).send({ message: "Error updating Servo angle" });
  }
};
