import serial

# Open serial port
ser = serial.Serial('COM9', 115200)  # Replace COM_PORT with your ESP32's port

# Open the file to write the image data
with open('captured_image.jpg', 'wb') as img_file:
    while True:
        byte_data = ser.read(1)
        if byte_data:
            img_file.write(byte_data)
        else:
            break
