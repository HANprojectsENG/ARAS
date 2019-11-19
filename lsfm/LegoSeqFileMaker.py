from appJar import gui
import numpy as np
import time
import datetime
import subprocess
import sys
import os
from os.path import dirname, abspath

RootPath = dirname(dirname(abspath(__file__)))

#constants
ORANGE = 106 
GREEN = 37 
YELLOW = 24 
BLUE = 23 
RED = 21

MAX_LAYERS = 20
MAX_LEGO_PER_LAYER = 50 
MAX_DATA_PER_LEGO = 28

#globals yey
SeletedColor = 21
SelectedStep = 0
SelectedLayer = 0
SelectedLegoSize = 0

addToSingleArrayINDX = 0
maxDataREached = False

matrix = np.zeros((MAX_LAYERS, MAX_LEGO_PER_LAYER, MAX_DATA_PER_LEGO), dtype=np.uint32)
localArray = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)

# handle button events
def press(button):
    if button == "Cancel":
        app.stop()
    elif button == "nextStep":
        nextStep()
    elif button == "emtpyStep":
        removeFromSingleArrayAll()
    elif button == "nextLayer":
        nextLayer()
    elif button == "emptyLayer":
        emptyLayer()
    elif button == "saveFile":
        saveFile()
    else:
        print("wtf")

def checkmarkStateChange(rb):
    coordinates = str(rb).split(",")
    if app.getCheckBox(str(rb)) and maxDataREached == False:
        app.setCheckBoxBoxBg(str(rb), returnColorStr(SeletedColor))
        #add to array here
        addToSingleArray(coordinates, rb)
    else:
        app.setCheckBoxBoxBg(str(rb), "white")
        #remove from array here
        removeFromSingleArray(coordinates, rb)

def colorSelectStateChange(rb):
    global SeletedColor
    SeletedColor = returnColorInt(app.getRadioButton("color"))
    
def returnColorInt(color):
    colorInt = 0
    if color == "red":
        colorInt = RED
    elif color == "blue":
        colorInt = BLUE
    elif color == "yellow":
        colorInt = YELLOW
    elif color == "green":
        colorInt = GREEN
    elif color == "orange":
        colorInt = ORANGE
    else:
        colorInt = 0
        print("WTF? color int failed")
    return colorInt

def returnColorStr(color):
    colorStr = ""
    if color == RED:
        colorStr = "red"
    elif color == BLUE:
        colorStr = "blue"
    elif color == YELLOW:
        colorStr = "yellow"
    elif color == GREEN:
        colorStr = "green"
    elif color == ORANGE:
        colorStr = "orange"
    else:
        colorStr = ""
        print("WTF? color str failed")
    return colorStr

def addToSingleArray(coordinates, rb):
    global addToSingleArrayINDX
    global maxDataREached
    global SelectedLegoSize
    localArray[0] = SelectedLayer
    localArray[1] = SelectedStep
    localArray[3] = SeletedColor
    if addToSingleArrayINDX < 23:
        xpos = int(coordinates[0])
        ypos = int(coordinates[1])
        localArray[4+addToSingleArrayINDX] = xpos
        localArray[5+addToSingleArrayINDX] = ypos
        addToSingleArrayINDX = addToSingleArrayINDX + 2
        app.setCheckBoxText(rb, str(SelectedLegoSize))
        SelectedLegoSize = SelectedLegoSize + 1
    else:
        print("oouuuff")
        maxDataREached = True
        app.setCheckBoxBoxBg(str(rb), "white")
        

def removeFromSingleArray(coordinates, rb):
    global maxDataREached
    global addToSingleArrayINDX
    global SelectedLegoSize
    addToSingleArrayINDX = addToSingleArrayINDX - 2
    xpos = int(coordinates[0])
    ypos = int(coordinates[1])
    if localArray[4+addToSingleArrayINDX] == xpos and localArray[5+addToSingleArrayINDX] == ypos:
        maxDataREached = False
        localArray[4+addToSingleArrayINDX] = 0
        localArray[5+addToSingleArrayINDX] = 0
        app.setCheckBoxText(rb, "  ")
        SelectedLegoSize = SelectedLegoSize - 1
    else:
        addToSingleArrayINDX = addToSingleArrayINDX + 2
    print("REMOVED")

def removeFromSingleArrayAll():
    global maxDataREached
    global addToSingleArrayINDX
    global localArray
    global SelectedLegoSize
    addToSingleArrayINDX = addToSingleArrayINDX - 2
    while addToSingleArrayINDX >= 0:
        xpos = localArray[4+addToSingleArrayINDX]
        ypos = localArray[5+addToSingleArrayINDX]
        index = str(xpos) + "," + str(ypos)
        app.setCheckBox(index, ticked=False, callFunction=False)
        app.setCheckBoxBoxBg(index, "white")
        addToSingleArrayINDX = addToSingleArrayINDX - 2
    localArray = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
    addToSingleArrayINDX = 0
    SelectedLegoSize = 0
    maxDataREached = False
    print("REMOVED ALL")

def emptyLayer():
    global maxDataREached
    global addToSingleArrayINDX
    global localArray
    global SelectedLegoSize
    global SelectedStep
    for x in range(11,36):
        for y in range(11,36):
            index = str(x) + "," + str(y)
            app.setCheckBox(index, ticked=False, callFunction=False)
            app.setCheckBoxBoxBg(index, "white")
    localArray = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
    addToSingleArrayINDX = 0
    SelectedLegoSize = 0
    SelectedStep = 0
    maxDataREached = False
    app.setLabel("stepLabel", ("Step: " + str(SelectedStep)))

def nextStep():
    global SelectedStep
    global addToSingleArrayINDX
    global SelectedLegoSize
    global localArray
    if SelectedLegoSize >= 2:
        localArray[2] = SelectedLegoSize
        localArray[3] = SeletedColor
        for i in range(0, MAX_DATA_PER_LEGO):
            matrix[SelectedLayer, SelectedStep, i] = localArray[i]
        SelectedStep = SelectedStep + 1
        addToSingleArrayINDX = addToSingleArrayINDX - 2
        while addToSingleArrayINDX >= 0:
            xpos = localArray[4+addToSingleArrayINDX]
            ypos = localArray[5+addToSingleArrayINDX]
            index = str(xpos) + "," + str(ypos)
            app.setCheckBox(index, ticked=False, callFunction=False)
            addToSingleArrayINDX = addToSingleArrayINDX - 2
        localArray = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
        addToSingleArrayINDX = 0
        SelectedLegoSize = 0
        app.setLabel("stepLabel", ("Step: " + str(SelectedStep)))
        print("axne!")
    else:
        print("oups")

def nextLayer():
    global maxDataREached
    global addToSingleArrayINDX
    global localArray
    global SelectedLegoSize
    global SelectedStep
    global SelectedLayer
    for x in range(11,36):
        for y in range(11,36):
            index = str(x) + "," + str(y)
            app.setCheckBox(index, ticked=False, callFunction=False)
            app.setCheckBoxBoxBg(index, "white")
    localArray = np.zeros((MAX_DATA_PER_LEGO), dtype=np.uint32)
    addToSingleArrayINDX = 0
    SelectedLegoSize = 0
    SelectedStep = 0
    maxDataREached = False
    SelectedLayer = SelectedLayer + 1
    app.setLabel("layerLabel", ("Layer: " + str(SelectedLayer)))
    app.setLabel("stepLabel", "Step: 0")


def saveFile():
    saveLocation = app.saveBox(title="Save lsf file", fileName="LegoSequenceFile", dirName=None, fileExt=".lsf", fileTypes=[('Lego Sequence File', '*.lsf')], asFile=None, parent=None)
    if saveLocation == '':
        return 0
    else:
        currentDate = datetime.datetime.now()
        file = open(saveLocation,"w+")
        file.write("File generated with Lego Sec File Maker at " + str(currentDate) + " \n") 
        layer = 0
        for layer in range(0, MAX_LAYERS):
            step = 0
            if matrix[layer, step, 2] != 0:
                file.write("This is Layer: " + str(layer) + "\n")
                for step in range(0, MAX_LEGO_PER_LAYER):
                    if matrix[layer, step, 2] != 0:
                        totals = 4 + matrix[layer, step, 2] * 2
                        finalstring = ""
                        for index in range(0, totals):
                            if index == totals - 1:
                                finalstring = finalstring + str(matrix[layer, step, index]) + "\n"
                            else:
                                finalstring = finalstring + str(matrix[layer, step, index]) + ", "
                        file.write(finalstring) 
        file.close() 



app = gui("Lego Seq File Maker", "1000x900")
app.setFont(9)

app.startFrame("TOP", row=0, column=0)

for x in range(11,36):
    for y in range(11,36):
        index = str(x) + "," + str(y)
        app.addNamedCheckBox("  ", index, row=x, column=y)
        app.setCheckBoxChangeFunction(index, checkmarkStateChange)

app.stopFrame()

app.startFrame("BOTTOM", row=36, column=0)
app.startPanedFrame("p1")

app.addNamedButton("Next Step", "nextStep", press)
app.addNamedButton("Next Layer", "nextLayer", press)
app.addNamedButton("Empty Step", "emtpyStep", press)
app.addNamedButton("Empty Layer", "emptyLayer", press)

app.startPanedFrame("p2")

app.addLabel("layerLabel", "Layer: 0")
app.addLabel("stepLabel", "Step: 0")
app.addNamedButton("Save File", "saveFile", press)

app.stopPanedFrame()

app.startPanedFrame("p3")

app.addRadioButton("color", "red")
app.addRadioButton("color", "blue")
app.addRadioButton("color", "yellow")
app.addRadioButton("color", "green")
app.addRadioButton("color", "orange")

app.stopPanedFrame()
app.stopPanedFrame()

# call this function, when the RadioButton changes
app.setRadioButtonChangeFunction("color", colorSelectStateChange)

app.stopFrame()
# start the GUI
app.go()
