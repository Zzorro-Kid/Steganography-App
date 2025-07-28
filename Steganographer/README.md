# Steganographer App

Steganographer is a C++ CLI tool for performing steganography on BMP and PPM image files. 
It allows to embed hidden messages within images and extract them later


## ✨ Features

* **View Image Information**: Display details about BMP and PPM image files, including dimensions, size, and last modified date
* **Embed Messages**: Hide text messages within BMP (24-bit) and PPM (P3/P6) images
* **Extract Messages**: Retrieve hidden messages from steganographically altered BMP and PPM images
* **Check Capacity**: Determine if an image has enough capacity to embed a given message
* **Supported Formats**: BMP (24-bit) and PPM (P3 and P6)


## 🛠 Prerequisites

  - CMake 
  - C++ compiler 

  
## 🚀 Install, Build & Run the project:

  1. **Clone or download** this repository & navigate to proj. directory:

    git clone https://github.com/Zzorro-Kid/Steganography-App.git
    cd Steganographer

  2. Build it and Compile:

    mkdir build
    cd build
    cmake .. && make

  3. Run the application:

    ./Steganographer


## 👨‍💻 Usage  

  The application has 4 main tabs:

   1. File Info:

      - View technical details about image files;

      - Shows format, dimensions, size, and modification date;

   2. Embed Message:

      - Select an image file;

      - Enter your secret message;

      - Click "Embed message" to hide the message in the image;

   3. Extract Message:

      - Select a steganographic image;

      - Click "Extract message" to reveal the hidden content;

   4. Check Capacity:

      - Verify if an image has enough space for your message;

      - Enter a test message to check capacity;
