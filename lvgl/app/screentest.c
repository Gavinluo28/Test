#include "screentest.h"
#include "lvgl.h"
#include "stdio.h"
#include "dht11.h"
#include "gui_guider.h"
#include "events_init.h"
extern lv_ui gui_ui;
extern DHT11   dht11;
char tembuf[20]={0};
char humbuf[20]={0};
void screen_test(void)
{
	lv_obj_t * scr1 = lv_obj_create(NULL, NULL);//创建屏幕1
	lv_obj_t * label1 = lv_label_create(scr1, NULL);//在屏幕1创建文本1
	lv_obj_t * label2 = lv_label_create(scr1, NULL);//在屏幕1创建文本2
	sprintf(tembuf,"%.2f",dht11.tem);
	lv_label_set_text_fmt(label1, "tem:%s",tembuf);
	lv_scr_load(scr1);//加载屏幕1
	lv_task_handler();
}







