// message queue: FIFO - pop somethign to the message queue, all the children try to grab it
//
#include <mqueue.h>

struct Data {
	char key[32];
	double value;

}
// sender
int main() {
	if (argc < 4) {
		printf("error");
		return 1;
	}	

}


// reciever
//
int main() {
	
	// what mq returns
	
	mqd_t mq;
	struct Data data;
	ssize_t bytes;
	unsigned int prio;
	// open up message queue of file argv1
	mq = mq_open(argv[1], O_RDONLY,); 

	for (;;) {
		bytes = mq_recieve(mq, (char*)&data, sizeof(data), &prio);
	}
	mq_close(mq);
}
