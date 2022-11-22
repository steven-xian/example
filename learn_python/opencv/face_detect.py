import cv2

if __name__ == '__main__':
    cap = cv2.VideoCapture(0)
    face_detector = cv2.CascadeClassifier('./haarcascade_frontalface_alt.xml')

    while True:
        flag, frame = cap.read()

        if not flag:
            break

        gray = cv2.cvtColor(frame, code=cv2.COLOR_BGR2GRAY)
        faces = face_detector.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=10)
        for x,y,w,h in faces:
            cv2.rectangle(frame, pt1 = (x, y), pt2 = (x + w, y + h), color = [0, 0, 255], thickness = 2)

        cv2.imshow('face', frame)
        key = cv2.waitKey(1000 // 24)
        if key == ord('q'):
            break

    cv2.destroyAllWindows()
    cap.release()