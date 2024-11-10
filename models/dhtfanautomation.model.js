import mongoose from "mongoose";

const dhtfanautomationSchema = new mongoose.Schema(
  {
    isActive: {
      type: Boolean,
      default: true,  // Automation is enabled by default
    },
  },
  { timestamps: true }
);

const Dhtfanautomation = mongoose.model("Dhtfanautomation", dhtfanautomationSchema);

export default Dhtfanautomation;
