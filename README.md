# Quad Trees


To download our program, please copy and paste this line to your terminal:
```
git clone https://github.com/agjignesh/CS201_Final_Project.git
```
Then type
```
cd CS201_Final_Project
```
### First you will need to decide if you want to simulate 2D Point Quad Tree or Image Compression Quad Tree:
To simulate 2D Points quad tree, type ``` gcc quad_trees.c -o quad_tree_point ``` and then type ``` ./quad_tree_point ``` in your terminal. 
To simulate image compression, refer bellow.

---

### Steps to run Image Compression
It is expected that your system has OpenCV library installed. If not steps for the same are given below.

***Steps to install OpenCV***

Build and install OpenCV in your machine if you already haven't. Here are guides to do the same:
* [For Ubuntu](http://techawarey.com/programming/install-opencv-c-c-in-ubuntu-18-04-lts-step-by-step-guide/) 
* [For Windows](https://cv-tricks.com/how-to/installation-of-opencv-4-1-0-in-windows-10-from-source/)
* [For MacOS](https://docs.opencv.org/master/d0/db2/tutorial_macos_install.html)

After installing OpenCV,type the below command in your terminal:
```
g++ quadtree_image_compression.cpp -o test -std=c++11 `pkg-config --cflags --libs opencv`
```
This will generate an output file ***test.exe***. To run this file type ```./test```  or ```./test.exe``` in your terminal.
### Further Common Steps for any OS

After this the programme will ask you the path of image which is to compressed. After you enter the required path, it will ask you to enter Y if you want to change the default threshold value and N if you want to go with default value only. This threshold value has been used for image compression. After giving the required inputs programme will diplay the percentage compression and display the original ans compressed image. The compressed file will also be saved with a name ***modified.jpeg*** in the directory where code is present. 

The code will terminate as soon as you close the images

---
**Mentor**
Anurag Jaiswal

**Group Members**
| Name            | Entry Number |
| --------------- | ------------ |
| Kritika Bansal | 2021CSB1184  |
| Manik Gupta | 2021MCB1187  |
| Jignesh Agrawal | 2021MCB1181  |
