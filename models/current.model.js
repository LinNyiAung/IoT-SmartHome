import mongoose from "mongoose";

const currentSchema = new mongoose.Schema(
    {
      voltage: {
        type: Number,
        required: true,
      },
      current: {
        type: Number,
        required: true,
      },
    },
    { timestamps: true }
  );
  const Current = mongoose.model('Current', currentSchema);

  export default Current;