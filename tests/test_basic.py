import cv2
import socket
import struct
import time
import os

async def test_basic(service_client):
    response = await service_client.get('/ping')
    assert response.status == 200

async def test_video(service_client):
    cap = cv2.VideoCapture("/home/user/service_template/tests/video/cat.mp4")

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(("localhost", 8010))

    try:
        fps = cap.get(cv2.CAP_PROP_FPS)
        frame_delay = 1 / fps if fps > 0 else 0.03  # 30 FPS

        while True:
            ret, frame = cap.read()
            if not ret:
                break

            _, jpeg = cv2.imencode(".jpg", frame, [int(cv2.IMWRITE_JPEG_QUALITY), 85])

            sock.sendall(jpeg.tobytes())

            time.sleep(frame_delay)

    finally:
        cap.release()
        sock.close()
