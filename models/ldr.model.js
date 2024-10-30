import mongoose from "mongoose";

const ldrSchema = new mongoose.Schema(
  {
    lightIntensity: {
      type: Number,  // Store the light intensity as a number
      required: true,
    },
  },
  { timestamps: true }
);

const LDR = mongoose.model('LDR', ldrSchema);

export default LDR;
