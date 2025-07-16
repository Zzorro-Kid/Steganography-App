# Steganographer

Steganographer is a C++ application built with the Qt framework that provides a graphical user interface for performing steganography on BMP and PPM image files. It allows to embed hidden messages within images and extract them later


## Features

* **View Image Information**: Display details about BMP and PPM image files, including dimensions, size, and last modified date
* **Embed Messages**: Hide text messages within BMP (24-bit) and PPM (P3/P6) images
* **Extract Messages**: Retrieve hidden messages from steganographically altered BMP and PPM images
* **Check Capacity**: Determine if an image has enough capacity to embed a given message
* **Supported Formats**: BMP (24-bit) and PPM (P3 and P6)


## How it Works

The application utilizes the Least Significant Bit (LSB) steganography technique. Messages are converted into a binary stream, and each bit of the message replaces the least significant bit of the image's pixel data.


## Getting Started


### Prerequisites

  - Qt 5 or Qt 6 development environment
  - CMake 
  - C++ compiler 

  
### Install & Build the project

    1. Clone or download this repository
