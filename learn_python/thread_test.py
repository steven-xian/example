import queue
import threading
import time
import random

exitFlag = 0

class myThread(threading.Thread):
    def __init__(self, threadId, name, q):
        threading.Thread.__init__(self)
        self.threadId = threadId
        self.name = name
        self.q = q

    def run(self) -> None:
        print("start thread:" + self.name)
        processData(self.name, self.q)
        print("quit thread:" + self.name)

def processData(threadName, q):
    while not exitFlag:
        # queueLock.acquire()
        if not workQueue.empty():
            data = q.get()
            # queueLock.release()
            print("%s processing %s" % (threadName, data))
            time.sleep(random.randint(1,5))
        # else:
            # queueLock.release()

threadList = ["Thread-1", "Thread-2", "Thread-3"]        
nameList = ["one", "two", "three", "four", "five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve"]
# queueLock = threading.Lock()
workQueue = queue.Queue(20)
threads = []
threadId = 1

for tName in threadList:
    thread = myThread(threadId, tName, workQueue)
    thread.start()
    threads.append(thread)
    threadId += 1

# queueLock.acquire()
for word in nameList:
    workQueue.put(word)
# queueLock.release()

while not workQueue.empty():
    pass

exitFlag = 1

for t in threads:
    t.join()

print("exit main thread")    