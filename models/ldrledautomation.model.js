import mongoose from "mongoose";

const ldrledautomationSchema = new mongoose.Schema(
  {
    isActive: {
      type: Boolean,
      default: true,  // Automation is enabled by default
    },
  },
  { timestamps: true }
);

const Ldrledautomation = mongoose.model("Ldrledautomation", ldrledautomationSchema);

export default Ldrledautomation;
