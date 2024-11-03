import mongoose from "mongoose";

const servoSchema = new mongoose.Schema(
  {
    angle: {
      type: Number,
      required: true,
      default: 0,
    },
  },
  { timestamps: true }
);

const Servo = mongoose.model('Servo', servoSchema);
export default Servo;
