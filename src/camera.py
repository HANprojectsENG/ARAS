import time
try:
    from picamera.array import PiRGBArray
    from picamera import PiCamera
except ImportError:
    print("Failed to load PiCamera. Expect errors when trying to read from the camera.")

CAPTURE_RESOLUTION = (1640, 1232)

cameraDevice = None


def init():
    global cameraDevice
    # initialize the camera and grab a reference to the raw camera capture
    captureResolution = (1640, 1232)
    cameraDevice = PiCamera()
    cameraDevice.resolution = CAPTURE_RESOLUTION
    cameraDevice.framerate = 15
    cameraDevice.iso = 100
    cameraDevice.meter_mode = "matrix"
    cameraDevice.awb_mode = "fluorescent"

    # allow the camera to warmup
    time.sleep(0.1)

def capture():
    rawCapture = PiRGBArray(cameraDevice, size=CAPTURE_RESOLUTION)
    cameraDevice.capture(rawCapture, format="bgr", use_video_port=True)

    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
    image = rawCapture.array

    return image
