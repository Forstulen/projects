from PIL import Image, ImageDraw
import aggdraw
import sys
import getopt
import math
import os
import numpy

def main(argv):
    inputFile = ''
    nbSquare = 25
    colorMethod = "center"

    try:
        opts, args = getopt.getopt(sys.argv[1:], "f:i:m:", ["file=", "iter=", "method="])
    except getopt.GetoptError as err:
        print str(err)
        sys.exit(2)
    for o, a in opts:
        if o in ("-h", "--help"):
            print "main.py -f filename -i nbIterations"
            sys.exit()
        elif o in ("-f", "--file"):
            inputFile = a
            print inputFile
        elif o in ("-i", "--iter"):
            nbSquare = int(a)
            print nbSquare
        elif o in ("-m", "--method"):
            colorMethod = a
            print nbSquare
        else:
            assert False, "unhandled option"
    
    inputImage = Image.open(inputFile)
    outputImage = Image.new(inputImage.mode, inputImage.size)

    width, height = inputImage.size
    
    stepX = int(math.ceil(width / nbSquare))
    stepY = stepX

    coordX = 0
    coordY = 0

    drawObj = aggdraw.Draw(outputImage)
    drawObj.setantialias(True)

    print "Width " + str(width) + " height " + str(height)

    for i in range(nbSquare):
        coordX = 0
        for j in range(nbSquare):
            valueX = width - 1
            valueY = height - 1
            if colorMethod == "center":
                if int((coordX + coordX + (stepX / 2) + coordX) / 3) < width:
                    valueX = int((coordX + coordX + (stepX / 2) + coordX) / 3)
                if int((coordY + coordY + (stepY / 2) + coordY + stepY) / 3) < height:
                    valueY = int((coordY + coordY + (stepY / 2) + coordY + stepY) / 3)
                color = aggdraw.Brush(inputImage.getpixel((valueX, valueY)))
            elif colorMethod == "3vertices":
                color1 = inputImage.getpixel((coordX if coordX < width else width - 1, 
                                                           coordY if coordY < height else height - 1))
                color2 = inputImage.getpixel((coordX + stepX / 2 if coordX + stepX / 2 < width else width - 1, 
                                                            coordY + stepY / 2 if coordY + stepY / 2 < height else height - 1))
                color3 = inputImage.getpixel((coordX if coordX < width else width - 1, 
                                                            coordY + stepY if coordY + stepY < height else height - 1))
                color = aggdraw.Brush(((color1[0] + color2[0] + color3[0]) / 3, 
                        (color1[1] + color2[1] + color3[1]) / 3, 
                        (color1[2] + color2[2] + color3[2]) / 3))
            drawObj.polygon((coordX, coordY, coordX + stepX / 2, coordY + stepY / 2, 
                            coordX, coordY + stepY), color)

            valueX = width - 1
            valueY = height - 1
            if colorMethod == "center":
                if int((coordX + coordX + (stepX / 2) + coordX + stepX) / 3) < width:
                    valueX = int((coordX + coordX + (stepX / 2) + coordX + stepX) / 3)
                if int((coordY + coordY + (stepY / 2) + coordY) / 3) < height:
                    valueY = int((coordY + coordY + (stepY / 2) + coordY) / 3)
                color = aggdraw.Brush(inputImage.getpixel((valueX, valueY)))
            elif colorMethod == "3vertices":
                color1 = inputImage.getpixel((coordX if coordX < width else width - 1, 
                                                           coordY if coordY < height else height - 1))
                color2 = inputImage.getpixel((coordX + stepX / 2 if coordX + stepX / 2 < width else width - 1, 
                                                            coordY + stepY / 2 if coordY + stepY / 2 < height else height - 1))
                color3 = inputImage.getpixel((coordX + stepX if coordX + stepX < width else width - 1, 
                                                            coordY if coordY < height else height - 1))
                color = aggdraw.Brush(((color1[0] + color2[0] + color3[0]) / 3, 
                        (color1[1] + color2[1] + color3[1]) / 3, 
                        (color1[2] + color2[2] + color3[2]) / 3))
            drawObj.polygon((coordX, coordY, coordX + stepX / 2, coordY + stepY / 2,
                            coordX + stepX, coordY), color)

            valueX = width - 1
            valueY = height - 1
            if colorMethod == "center":
                if int((coordX + coordX + (stepX / 2) + coordX + stepX) / 3) < width:
                    valueX = int((coordX + coordX + (stepX / 2) + coordX + stepX) / 3)
                if int((coordY + stepY + coordY + (stepY / 2) + coordY + stepY) / 3) < height:
                    valueY = int((coordY + stepY + coordY + (stepY / 2) + coordY + stepY) / 3)
                color = aggdraw.Brush(inputImage.getpixel((valueX, valueY)))
            elif colorMethod == "3vertices":
                color1 = inputImage.getpixel((coordX if coordX < width else width - 1, 
                                                           coordY + stepY if coordY + stepY < height else height - 1))
                color2 = inputImage.getpixel((coordX + stepX / 2 if coordX + stepX / 2 < width else width - 1, 
                                                            coordY + stepY / 2 if coordY + stepY / 2 < height else height - 1))
                color3 = inputImage.getpixel((coordX + stepX if coordX + stepX < width else width - 1, 
                                                            coordY + stepY if coordY + stepY < height else height - 1))
                color = aggdraw.Brush(((color1[0] + color2[0] + color3[0]) / 3, 
                        (color1[1] + color2[1] + color3[1]) / 3, 
                        (color1[2] + color2[2] + color3[2]) / 3))
            drawObj.polygon((coordX, coordY + stepY, coordX + stepX / 2, coordY + stepY / 2,
                            coordX + stepX, coordY + stepY), color)

            valueX = width - 1
            valueY = height - 1
            if colorMethod == "center":
                if int((coordX + stepX + coordX + (stepX / 2) + coordX + stepX) / 3) < width:
                    valueX = int((coordX + stepX + coordX + (stepX / 2) + coordX + stepX) / 3)
                if int((coordY + coordY + (stepY / 2) + coordY + stepY) / 3) < height:
                    valueY = int((coordY + coordY + (stepY / 2) + coordY + stepY) / 3)
                color = aggdraw.Brush(inputImage.getpixel((valueX, valueY)))
            elif colorMethod == "3vertices":
                color1 = inputImage.getpixel((coordX + stepX if coordX + stepX < width else width - 1, 
                                                           coordY if coordY < height else height - 1))
                color2 = inputImage.getpixel((coordX + stepX / 2 if coordX + stepX / 2 < width else width - 1, 
                                                            coordY + stepY / 2 if coordY + stepY / 2 < height else height - 1))
                color3 = inputImage.getpixel((coordX + stepX if coordX + stepX < width else width - 1, 
                                                            coordY + stepY if coordY + stepY < height else height - 1))
                color = aggdraw.Brush(((color1[0] + color2[0] + color3[0]) / 3, 
                        (color1[1] + color2[1] + color3[1]) / 3, 
                        (color1[2] + color2[2] + color3[2]) / 3))
            drawObj.polygon((coordX + stepX, coordY, coordX + stepX / 2, coordY + stepY / 2, 
                             coordX + stepX, coordY + stepY), color)
            coordX += stepX
        coordY += stepY

    drawObj.flush()
    fileName, fileExtension = os.path.splitext(inputFile)
    outputImage.save(fileName + str(nbSquare) + "iter_" + colorMethod + fileExtension)

if __name__ == "__main__":
    main(sys.argv[1:])
