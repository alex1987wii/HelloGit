#include <stdio.h>
#define EVENT_MAX		256
#define MSG1	1
#define MSG2	2
#define MSG3	3
typedef void (*event_handler_t)(void);

struct event_map{
	int event;
	event_handler_t handler;
};
event_handler_t evt_map[EVENT_MAX];
/*
struct event_queue{
	int head,tail;
	int event[EVENT_MAX];
}evt_queue;
*/
void postEvt(int evt)
{
	evt_queue.event[evt_queue.head++] = evt;
	evt_queue.head %= EVENT_MAX;
}
__attribute__((destructor)) void destory_evt_map(void)
{
	int i = 0;
	for(; i < EVENT_MAX; ++i)
	{
		evt_map[i] = NULL;
	}
}
void evt1_handler(void)
{
	printf("%s called\n",__func__);
	printf("postEvt(MSG2)\n");
	postEvt(MSG2);
	printf("postEvt(MSG3)\n");
	postEvt(MSG3);
}
void evt2_handler(void)
{
	printf("%s called\n",__func__);
	destory_evt_map();

}
void evt3_handler(void)
{
	printf("%s called\n",__func__);
}
void evt_process(void)
{
	if(evt_queue.head != evt_queue.tail)
	{
		event_handler_t handler = evt_map[evt_queue.event[evt_queue.tail++]];
		evt_queue.tail %= EVENT_MAX;
		if(handler)
			handler();
	}
	else
		sleep(1);
}
__attribute__((constructor)) void init_evt_map(void)
{
	evt_map[MSG1] = evt1_handler;
	evt_map[MSG2] = evt2_handler;
	evt_map[MSG3] = evt3_handler;
	postEvt(MSG1);
}
int main(void)
{
	while(1)
		evt_process();

	return 0;
}

