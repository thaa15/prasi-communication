#include <lxpanel/plugin.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <wiringPiI2C.h>

#define DEVICE_ID 0x3C
#define SLAVE_R4F 0x4F

static int getData(){
	int fd = wiringPiI2CSetup(DEVICE_ID);
	wiringPiI2CWrite(fd,SLAVE_R4F);
	int received_data = wiringPiI2CRead(fd);
	return received_data;
}

typedef struct {
  gint iBatt;
} BattPlugin;

GtkWidget *battery_constructor(LXPanel *panel, config_setting_t *settings)
{
 /* panel is a pointer to the panel and
     settings is a pointer to the configuration data
     since we don't use it, we'll make sure it doesn't
     give us an error at compilation time */
	 (void)panel;
	 (void)settings;
	 BattPlugin *pTest = g_new0(BattPlugin, 1);
	 pTest->iBatt = getData();

	 // make a label out of the battery I2C
	 char cIdBuf[4] = {'\0'};
	 
	 sprintf(cIdBuf, "%d%%", pTest->iBatt);

	 // create a label widget instance
	 GtkWidget *pLabel = gtk_label_new(cIdBuf);

	 // set the label to be visible
	 gtk_widget_show(pLabel);

	 // need to create a container to be able to set a border
	 GtkWidget *p = gtk_event_box_new();

	 // our widget doesn't have a window...
	 // it is usually illegal to call gtk_widget_set_has_window() from application but for GtkEventBox it doesn't hurt
	 gtk_widget_set_has_window(p, FALSE);
	 lxpanel_plugin_set_data(p, pTest, g_free);

	 // set border width
	 gtk_container_set_border_width(GTK_CONTAINER(p), 1);

	 // add the label to the container
	 gtk_container_add(GTK_CONTAINER(p), pLabel);

	 // set the size we want
	 // gtk_widget_set_size_request(p, 100, 25);

	 // success!!!
	 return p;
}

FM_DEFINE_MODULE(lxpanel_gtk, battery)

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name = "BatterySW6106",
   .description = "Display battery I2C",
   //.one_per_system = 1,

   // assigning our functions to provided pointers.
   .new_instance = battery_constructor
};
