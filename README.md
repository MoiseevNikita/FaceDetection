# Face Detection CLI and GUI applications

In this repository you will find two applications with Command Line and Graphical User Interfaces for detecting people's faces on images. They use the same library located in `FaceDetectionLIB` directory.

## CLI

### Description
CLI application requires path to images to be passed as command line arguments. As a result, this application will print a JSON document that contains information about faces it found on each image file. Files that do not exist or do not contain image data will be ignored and will not be present in the output JSON document.

### Output example

```bash
./FaceDetectionCLI non_existing_file.bmp image_with_no_faces.jpeg lena.jpg 
```
```json
{
    "image_with_no_faces.jpeg": [
    ],
    "lena.jpg": [
        {
            "age": {
                "mean": 23.7863,
                "variance": 51.5524
            },
            "coordinates": {
                "height": 334,
                "width": 334,
                "x": 438,
                "y": 459
            },
            "gender": "female"
        }
    ]
}
```

### Building and Running

```bash
mkdir FaceDetectionCLI/build && cd FaceDetectionCLI/build
cmake ..
make -j
./FaceDetectionCLI <path to image file> [<path to image file> [<path to image file>] [...]]
```

## GUI

### Description

GUI application allows users to select image files (in JPEG or BMP formats) or directories (in which case it will be searched nonrecursively with all it's JPEG and BMP files selected) via file dialog.  
After images are selected, they will appear in the main window with 'Processing...'  annotation at the center of each image and progress bar appearing at the bottom of main window. You can use mouse wheel to zoom image in and out.
When an image is processed, 'Processing...' annotation is removed and information about each face is displayed. When all images have been processed, progress bar will dissappear.

### Screenshot
![](screenshot.png)

### Building and Running

```bash
mkdir FaceDetectionGUI/build && cd FaceDetectionGUI/build
cmake ..
make -j
./FaceDetectionGUI
```