// Define the variables for the sensor data
var soilValue = 1000; // Adjust this value according to your sensor reading
var gasValue = 50; // Adjust this value according to your sensor reading
var soilStatus = "Wet"; // Adjust this value according to your sensor reading

// Create a JSON object to store the sensor data
var data = {
    "soilValue": soilValue,
    "gasValue": gasValue,
    "soilStatus": soilStatus
};

// Export the JSON object as a module
export default data;
