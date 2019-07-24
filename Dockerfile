FROM ubuntu:18.04

RUN apt update && apt install -y \
    qt5-default \
    build-essential \
    cmake

# Copy all files from git repository to /home/ directory
COPY / /home/

# Build CLI application
RUN rm -rf /home/FaceDetectionCLI/build && \
    mkdir  /home/FaceDetectionCLI/build
RUN cd /home/FaceDetectionCLI/build && \
    cmake .. && \
    cmake --build . && \
    cpack

# Build GUI application
RUN rm -rf /home/FaceDetectionGUI/build && \
    mkdir  /home/FaceDetectionGUI/build
RUN cd /home/FaceDetectionGUI/build && \
    cmake .. && \
    cmake --build . && \
    cpack

# Copy resulting .deb packages to host
CMD cp  /home/FaceDetectionCLI/build/*.deb \
        /home/FaceDetectionGUI/build/*.deb \
        /mnt/
