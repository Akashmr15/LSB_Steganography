# LSB_Steganography

LSB Digital Steganography
Steganography is the practice of representing information within another message or physical object, in such a manner that the presence of the information is not evident to human inspection. This project implements Least Significant Bit (LSB) digital steganography to hide a text message within a .bmp image file. The project includes a C program for encoding the message into the image and decoding the message from the image.

**How it Works**

The LSB digital steganography technique involves replacing the least significant bit of each byte in the image with the bits of the message to be hidden. Since the least significant bit has the least impact on the visual appearance of the image, this method allows for hiding data without noticeably altering the image.

**Features**

* Encoding: Embedding a text message into the least significant bits of a BMP image.
* We are using MAGIC_STRING as a password for authentication.
* Decoding: Extracting a hidden message from the least significant bits of a BMP image.
* Supports BMP Images: The program specifically works with BMP (Bitmap) images for steganography operations.

**Steps to Encoding :**
* Run the encode.c program, providing the path to the input image file (.bmp) and the text file containing the message to be hidden.
* The program will create a copy of the input image with the message encoded into it.

**Steps to Decoding :**
* Run the decode.c program, providing the path to the encoded image file (the output of the encoding process).
* The program will extract the hidden message from the image and store to new file.

**File Structure**
* ```encode.c``` : C program for encoding a text message into a .bmp image file.
* ```decode.c``` : C program for decoding a text message from a .bmp image file.
* ```beautiful.bmp``` : Sample input image file.
* ```secret.txt``` : Sample text file containing the message to be hidden.
* ```output.bmp``` : Output image file with the hidden message encoded.
* ```Makefile``` : File for running the code.
![Screenshot (36)](https://github.com/user-attachments/assets/a09a5b34-aef9-46da-b3a5-be557cb177d6)

**Requirements**

1) C Compiler (e.g., GCC)
2) .bmp image file
3) Text file containing the message to be hidden

**Example**

-> Encoding Use command :- ./output.exe -e beautiful.bmp secret.txt
![Screenshot (37)](https://github.com/user-attachments/assets/a857d0f9-a4b7-48ad-bd0c-d374edbe0aa9)

-> Decoding Use command :- ./final.exe -d output.bmp

![Screenshot (38)](https://github.com/user-attachments/assets/3cd9230a-f263-4233-b155-2ee1420e3815)

**Contributing**

Contributions are welcome! Please open an issue or submit a pull request for any new features, enhancements, or bug fixes.

**Acknowledgments**

This project was inspired by the concept of LSB steganography and aims to provide a simple implementation for educational purposes.
