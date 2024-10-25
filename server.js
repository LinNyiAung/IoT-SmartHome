import express from "express";
import LED from "./models/sensor.model.js";
import dotenv from "dotenv";
import mongoose from "mongoose";
import cors from "cors";
import ledRoutes from "./routes/sensor.route.js";
dotenv.config();



const app = express();
app.use(cors());
app.use(express.json());


// Connect to MongoDB Atlas
mongoose.connect(process.env.MONGO)
  .then(() => console.log('Connected to MongoDB Atlas'))
  .catch(err => console.log('MongoDB Atlas connection error:', err));



// Use LED routes
app.use('/api/led', ledRoutes);

// Start the server
const PORT = 5000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
