// Cody's PROS + Holonomic Code
// =======================
// Usage:	Drive code for "+" Holonomic drive
// License:	Public Domain, use at your own risk.

void holonomic() {
    //this code is horribly documented, test it to see what it does
    while(1) {
        
        // Controller 1/2, Stick L/R, Axis X/Y
        int C1LX = joystickGetAnalog(1, 4);
        int C1LY = joystickGetAnalog(1, 3);
        int C1RX = joystickGetAnalog(1, 1);
        
        // Y component, X component, Rotation
        motorSet(1, -C1LX - C1RX); // Front
        motorSet(2, -C1LY - C1RX); // Left
        motorSet(3,  C1LY - C1RX); // Right
        motorSet(4,  C1LX - C1RX); // Back
        
        // Motor values can only be updated every 20ms
        delay(20);
        
    }
    
}