import cv2
import apriltag
import serial
import time

# CHANGE, COM port and Phone IP addresses
ser = serial.Serial('COM3', 115200, timeout=1)

URL_FLOOR_PHONE = "http://192.168.1.50:8080/video"
URL_WALL_PHONE = "http://192.168.1.51:8080/video"

cap_floor = cv2.VideoCapture(URL_FLOOR_PHONE)
cap_wall = cv2.VideoCapture(URL_WALL_PHONE)

options = apriltag.DetectorOptions(families="tag36h11")
detector = apriltag.Detector(options)

while True:
    ret_f, frame_floor = cap_floor.read()
    ret_w, frame_wall = cap_wall.read()
    
    if not ret_f or not ret_w:
        print("CRITICAL: Network stream dropped!")
        # Send error state to force drone disarm
        ser.write(b"-1,-1,-1\n")
        break

    drone_x, drone_y, drone_z = -1, -1, -1

    gray_f = cv2.cvtColor(frame_floor, cv2.COLOR_BGR2GRAY)
    results_f = detector.detect(gray_f)
    if results_f:
        drone_x = int(results_f[0].center[0])
        drone_y = int(results_f[0].center[1])

    gray_w = cv2.cvtColor(frame_wall, cv2.COLOR_BGR2GRAY)
    results_w = detector.detect(gray_w)
    if results_w:
        img_height = frame_wall.shape[0]
        drone_z = img_height - int(results_w[0].center[1])

    if drone_x != -1 and drone_z != -1:
        print(f"Tracking -> X: {drone_x} | Y: {drone_y} | Z: {drone_z}")
    else:
        print("WARNING: Tracking lost on one or both cameras!")

    payload = f"{drone_x},{drone_y},{drone_z}\n"
    ser.write(payload.encode('utf-8'))

    time.sleep(0.02)

cap_floor.release()
cap_wall.release()