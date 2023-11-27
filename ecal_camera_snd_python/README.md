# Webcam Grabber

This sample code demonstrates how to read camera input as images and publish them on eCAL in protobuf format, as ROS compressed or raw images.

## Installation
It's recommended to start the `webcam-grabber` in a virtual environment.
Then install all necessary requirements
```
pip install -r ./requirements.txt
```
Additionaly, install the python wheel matching your python version, and operating system.
E.g. if you are using Python 3.11 64bit on a Windows operating system, and eCAL 5.12.1, run
```
pip install ./ecal5-5.12.1-cp311-cp311-win_amd64.whl
```
The eCAL wheels can be downloaded from the Github releases page [here](https://github.com/eclipse-ecal/ecal/releases).


## Usage
Run the python script `webcam-grabber.py`.
You will be able to see the published data in eCAL Monitor.

```
python .\ecal_camera_send\webcam-grabber.py --help
usage: webcam-grabber.py [-h] [--camera-id CAMERA_ID] [--compressed] [--topic-name TOPIC_NAME]

optional arguments:
  -h, --help            show this help message and exit
  --camera-id CAMERA_ID
                        Which camera to use for feed
  --compressed          send compressed image instead of raw image
  --topic-name TOPIC_NAME
                        topic name to publish
```