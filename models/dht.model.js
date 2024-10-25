import mongoose from "mongoose";

const dhtSchema = new mongoose.Schema(
    {
      temperature: {
        type: Number,
        required: true,
      },
      humidity: {
        type: Number,
        required: true,
      },
    },
    { timestamps: true }
  );
  const DHT = mongoose.model('DHT', dhtSchema);

  export default DHT;