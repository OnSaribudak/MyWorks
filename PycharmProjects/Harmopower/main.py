import cv2


faceCascade = cv2.CascadeClassifier("bebek.xml")

video_capture = cv2.VideoCapture(0)

while True:
    ret, frame = video_capture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(gray, 1.1, 5, minSize=(100, 100))
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        cv2.putText(frame, "Bebek Guvende", (x, y + h + 20), cv2.FONT_HERSHEY_DUPLEX, .5, (0, 255, 0))


    cv2.imshow('Video', frame)
    k = cv2.waitKey(1) & 0xFF
    if k == 27:
        break

video_capture.release()
cv2.destroyAllWindows()