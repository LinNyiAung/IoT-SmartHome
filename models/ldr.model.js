import mongoose from "mongoose";

const ldrSchema = new mongoose.Schema(
  {
    lightIntensity: {
      type: Boolean,  
      required: true,
    },
  },
  { timestamps: true }
);

const LDR = mongoose.model('LDR', ldrSchema);

export default LDR;
