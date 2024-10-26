import mongoose from "mongoose";

const pirSchema = new mongoose.Schema(
  {
    motion: {
      type: Boolean,
      required: true,
    },
  },
  { timestamps: true }
);

const PIR = mongoose.model('PIR', pirSchema);

export default PIR;
