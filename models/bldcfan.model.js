import mongoose from "mongoose";

const bldcfanSchema = new mongoose.Schema(
  {
    status: {
      type: String,
    },
  },
  { timestamps: true }
);
const BLDCFAN = mongoose.model('BLDCFAN', bldcfanSchema);

export default BLDCFAN;
