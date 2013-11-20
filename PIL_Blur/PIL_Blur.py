from PIL import Image, ImageDraw
import sys

def main(argv):
    image = Image.open("img.png")
    destination = Image.new(image.mode, image.size)
    #Change radius for an image with more blur
    radius = 7

    blur(image, destination, radius)
    destination.save("img_blurred.png")

def blur(image, dest, radius):
    pixSource = image.load()
    pixDest = dest.load()
    width, height = image.size
    #Little upgrade O(n^3) instead of O(n^4)
    horizontalBlurring(pixSource, pixDest, width, height, radius)
    verticalBlurring(pixSource, pixDest, width, height, radius)

def horizontalBlurring(pixSource, pixDest, width, height, radius):
    for y in range(height):
        for x in range(width):
            weight = [0, 0, 0]
            nbValue = 0
            for i in range(-radius, radius):
                #Check we stay in the image dimensions
                if x + i >= 0 and x + i < width:
                    nbValue += 1
                    #Add each RGB value from the radius square
                    weight = [value + add for value, add in zip(weight, pixSource[x + i, y])]
            pixDest[x, y] = tuple([color / nbValue for color in weight])

def verticalBlurring(pixSource, pixDest, width, height, radius):
    for y in range(height):
        for x in range(width):
            weight = [0, 0, 0]
            nbValue = 0
            for i in range(-radius, radius):
                #Check we stay in the image dimensions
                if y + i >= 0 and y + i < height:
                    nbValue += 1
                    #Add each RGB value from the radius square
                    weight = [value + add for value, add in zip(weight, pixSource[x, y + i])]
            pixDest[x, y] = tuple([color / nbValue for color in weight])


if __name__ == "__main__":
    main(sys.argv[1:])
