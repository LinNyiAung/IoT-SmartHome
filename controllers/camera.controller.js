export const getCameraStream = async (req, res) => {
    try {
      // Replace with the actual IP address of your ESP32 camera
      const cameraIP = "http://192.168.1.10"; 
      const response = await fetch(`${cameraIP}/capture`); // ESP32 endpoint to get images
      const imageBuffer = await response.arrayBuffer();
      res.writeHead(200, { "Content-Type": "image/jpeg" });
      res.end(Buffer.from(imageBuffer), "binary");
    } catch (error) {
      console.error("Error fetching camera stream:", error);
      res.status(500).send({ message: "Failed to fetch camera stream." });
    }
  };
  