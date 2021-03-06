# facerec-door-lock
Facial Recognition Door Lock Software for a Raspberry Pi 3 Model B with Raspberry Pi Camera Module v2, written in C++. This project is an adaptation of Tony DiCola's [Raspberry Pi Face Recognition Software in Python](https://learn.adafruit.com/raspberry-pi-face-recognition-treasure-box?view=all). Re-creating the project in C++ was a result of outdated Python2/3 bindings for OpenCV 3. This project uses the LBPH model for facial recognition.


Tested with: 
 - Raspberry Pi 3 Model B
 - Raspberry Pi Camera Module v2
 - OpenCV 3.4.0


 Setup:
  - Make sure the camera module in enabled with `sudo raspo-config`
  - Use `sudo modprobe bcm2835-v4l2` to create a device for the Camera Module at /dev/video0
  - Make sure OpenCV 3.4.0 or later is installed (__including OpenCV contrib__)(you may need to compile from source)
  - In the repository, run `make all` to build the executibles
  - To capture positive images (of allowed faces) run the `capture_postitives.out` program:
    - `./capture_positives.out <name>` (where name is the name of the person you are capturing)
    - Follow the prompts and take about 20 images of your subject
- After capturing positive images for everyone allowed through the door, train the model with the `train.out` program:
    - `./train.out <model_name>` will create a complete model
- Finally, to run the main lock program, use `./lock.out <model_name>`


### Virtual Environment
It is strongly recommended to use a Python virtual environment. To create a virtual env, use the `venv` feature of python3.
Run the command below in the root project directory. Recommended folder name for the virtual environment is `env`.
```
python3 -m venv <env-folder-name>
```

To activate that virtual environment, use the below command:
```
source <env-folder-name>/bin/activate
```

After activating, to install the dependencies run
```
pip3 install -r requirements.txt
```

