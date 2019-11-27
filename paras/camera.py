import time
import threading
from constants import CAPTURE_RESOLUTION
try:
    from picamera.array import PiRGBArray
    from picamera import PiCamera
except ImportError:
    print("Failed to load PiCamera. Expect errors when trying to read from the camera.")

cameraDevice = None
camera_thread_stop = True
currentImageCapture = None


def init():
    global cameraDevice
    # initialize the camera and grab a reference to the raw camera capture
    captureResolution = (1648, 1232)
    cameraDevice = PiCamera()
    cameraDevice.resolution = CAPTURE_RESOLUTION
    cameraDevice.framerate = 15
    cameraDevice.iso = 100
    cameraDevice.meter_mode = "matrix"
    cameraDevice.awb_mode = "auto"

    # allow the camera to warmup
    time.sleep(2)

    # Now fix the values
    cameraDevice.shutter_speed = cameraDevice.exposure_speed
    cameraDevice.exposure_mode = 'off'
    g = cameraDevice.awb_gains
    cameraDevice.awb_mode = 'off'
    cameraDevice.awb_gains = g


def VideoStream_thread():
    global currentImageCapture
    global cameraDevice
    rawCapture = PiRGBArray(cameraDevice, size=CAPTURE_RESOLUTION)
    stream = cameraDevice.capture_continuous(rawCapture, format="bgr", use_video_port=True)
    for f in stream:
        frame = f.array
        currentImageCapture = frame
        rawCapture.truncate(0)
        if camera_thread_stop:
            stream.close()
            rawCapture.close()
            cameraDevice.close()
            return

def capture():
    return currentImageCapture

def stop_VideoStream_thread():
    global camera_thread_stop
    camera_thread_stop = True

def start_VideoSream_thread(valid):
    global camera_thread_stop
    if valid == True and camera_thread_stop == True:
        camera_thread_stop = False
        thread2 = threading.Thread(target=VideoStream_thread, daemon=True)
        thread2.start()
