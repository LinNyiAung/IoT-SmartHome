import mongoose from "mongoose";

const ledSchema = new mongoose.Schema(
  {
    status: {
        type: String,
    }  // 'ON' or 'OFF'
  },{timestamps: true});
  const LED = mongoose.model('LED', ledSchema);

  export default LED;