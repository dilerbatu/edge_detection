
import glob
import cv2
import numpy as np

class EdgeDetector():

    #Empty "images" array. Unprocessed images will be added to it. (Class attribute)
    images = []

    #Empty "processed_images" array. Processed images will be added to it. (Class attribute)
    processed_images = []

    #Supported image extensions. (Class attribute)
    image_extensions = [".png", ".jpg", ".jpeg", ".JPG", ".PNG", ".JPEG"]

    def get_images(self):
        #This method serves to get all images from data folder.

        #Getting all image types.
        for extensions in self.image_extensions:
            self.images += sorted(glob.glob("data/*{}".format(extensions))) #Adding all images to "images" array. 

        print("All images fetched succesfuly.")
    
        
    def process_images(self):
        #This method serves to process all images.

        #All photos in images array are processed one by one.
        for image in self.images:
            
            img = cv2.imread(image) #Reading the image
            
            img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) #Grayscaling the image
            
            blured_image = cv2.GaussianBlur(img_gray, (3, 3), 0, 0) #Blurring the image
           
            edges = cv2.Canny(blured_image, 150 , 200 , apertureSize = 3) #Applying Canny Filter to image and getting edges

            #Using probabilistic hough line tranformation to find lines on the image. To get better performance, this paramaters can be changed.
            lines = cv2.HoughLinesP(image = edges, rho=1, theta= np.pi/180, threshold = 40, lines = np.array([]), minLineLength = 30 ,maxLineGap = 200)

        
            #lines is an array that holds all data of lines like start and end point of lines.
            #lines = [[[x1,y1,x2,y2],
            #          [x3,y3,x4,y4],
            #           ...........]]

            #For example; 
            #lines[0][0][0] gives x1 for line 0.
            #lines[0][0][1] gives y1 for line 0.
            #lines[0][0][2] gives x2 for line 0.
            #lines[0][0][3] gives y2 for line 0.

            
            count_of_lines = lines.shape[0] #lines.shape[0] gives number of rows which means count of lines.
            
            for line in range(count_of_lines): 

                #Indicating start and end point of the line.
                x2 = lines[line][0][0] 
                y2 = lines[line][0][1]
                x1 = lines[line][0][2]
                y1 = lines[line][0][3]

                start_point = (x1,y1)
                end_point = (x2,y2)

                #Drawing lines over the image.
                cv2.line(img, start_point, end_point, (0, 255, 0), 2, cv2.LINE_AA)

                
            #Adding image into processed_images array.
            self.processed_images.append(img)

        print("All images processed succesfuly.")
        
            
    def show_processed_images(self):
        #This method serves to display the processed images.

        #Checking "processed_images" array's size
        if len(self.processed_images) != 0:
            #Showing all images one by one
            for processed_image in self.processed_images:

                resized_image = cv2.resize(processed_image, (600, 600)) # For better view
                cv2.imshow('Result', resized_image)
                cv2.waitKey(0)
        else:
            print("Process the images first, to see the processed images.")


    def save_processed_images(self):
        #This method serves to save the processed images.

        #Checking "processed_images" array's size
        if len(self.processed_images) != 0:
            #Saving all images into output_python file.
            for count, processed_image in enumerate(self.processed_images):
                cv2.imwrite('outputs_python/output_{}.jpg'.format(count), processed_image)

            print("Saved to outputs_python file.")
        else:

            print("Process the images first, to save the processed images.")
        

if __name__ == "__main__":
    

    EdgeDetector().get_images()
    EdgeDetector().process_images()
    EdgeDetector().show_processed_images()
    EdgeDetector().save_processed_images()

