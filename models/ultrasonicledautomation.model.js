import mongoose from "mongoose";

const ultrasonicledautomationSchema = new mongoose.Schema(
  {
    isActive: {
      type: Boolean,
      default: true,  // Automation is enabled by default
    },
  },
  { timestamps: true }
);

const Ultrasonicledautomation = mongoose.model("Ultrasonicledautomation", ultrasonicledautomationSchema);

export default Ultrasonicledautomation;
