import mongoose from "mongoose";

const ultrasonicSchema = new mongoose.Schema(
  {
    distance: {
      type: Number,
      required: true,
    },
  },
  { timestamps: true }
);

const Ultrasonic = mongoose.model('Ultrasonic', ultrasonicSchema);

export default Ultrasonic;
