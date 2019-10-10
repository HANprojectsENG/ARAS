try:
    from picamera.array import PiRGBArray
    from picamera import PiCamera
except ImportError:
    print("Failed to load PiCamera. Expect errors when trying to read from the camera.")

CAPTURE_RESOLUTION = (1640, 1232)

camera = None


def init():
    # initialize the camera and grab a reference to the raw camera capture
    captureResolution = (1640, 1232)
    camera = PiCamera()
    camera.resolution = CAPTURE_RESOLUTION
    camera.framerate = 15
    camera.iso = 100
    camera.meter_mode = "matrix"
    camera.awb_mode = "fluorescent"

    # allow the camera to warmup
    time.sleep(0.1)


def capture():
    rawCapture = PiRGBArray(camera, size=captureResolution)
    camera.capture(rawCapture, format="bgr", use_video_port=True)

    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
    image = frame.array

    return image
