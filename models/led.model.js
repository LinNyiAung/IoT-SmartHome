import mongoose from "mongoose";

const ledSchema = new mongoose.Schema(
  {
    status: {
      type: String,
    },
  },
  { timestamps: true }
);
const LED = mongoose.model('LED', ledSchema);

export default LED;
