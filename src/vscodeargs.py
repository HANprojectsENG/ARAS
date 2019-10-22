import os

# Set to True is using the inferior VSCode for testing, False otherwise
UsingVSCode = False

cwd = os.getcwd()
VisualStudioArgImage = cwd.replace("src", "testimages\\test-markers.jpg")
VisualStudioArgFile = cwd.replace("src", "LegoSequenceFile.lsf")
VisualStudioSaveFile = cwd.replace("src", "Saved.gg")
