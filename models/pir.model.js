// pir.model.js
import mongoose from "mongoose";

const pirSchema = new mongoose.Schema(
  {
    motionDetected: {
      type: Boolean,
      required: true,
    },
  },
  { timestamps: true }
);

const PIR = mongoose.model('PIR', pirSchema);
export default PIR;
