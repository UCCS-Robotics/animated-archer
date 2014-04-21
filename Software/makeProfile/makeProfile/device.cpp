#include "device.h"
#include "ui_device.h"

Device::Device(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Device)
{
    ui->setupUi(this);
}

Device::~Device()
{
    delete ui;
}

int Device::identify(){
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL; //a libusb session
    int r; //for return values
    ssize_t cnt; //holding number of devices in list
    r = libusb_init(&ctx); //initialize a library session
    if(r < 0) {
        ui->plainTextEdit->insertPlainText("Init Error ");
        ui->plainTextEdit->insertPlainText(QString::number(r));
        ui->plainTextEdit->insertPlainText("\n");
        return 1;
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
    cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
    if(cnt < 0) {
        ui->plainTextEdit->insertPlainText("Get Device Error\n");
    }
    ui->plainTextEdit->insertPlainText(QString::number(cnt));
    ui->plainTextEdit->insertPlainText(" Devices in list.\n");
    ssize_t i; //for iterating through the list
    for(i = 0; i < cnt; i++) {
        printdev(devs[i]); //print specs of this device
    }
    libusb_free_device_list(devs, 1); //free the list, unref the devices in it
    libusb_exit(ctx); //close the session
    return 0;
}

void Device::printdev(libusb_device *dev){
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
        ui->plainTextEdit->insertPlainText("failed to get device descriptor\n");
        return;
    }
    ui->plainTextEdit->insertPlainText("Number of possible configurations: ");
    ui->plainTextEdit->insertPlainText(QString::number((int)desc.bNumConfigurations));
    ui->plainTextEdit->insertPlainText("  ");
    ui->plainTextEdit->insertPlainText("Device Class: ");
    ui->plainTextEdit->insertPlainText(QString::number((int)desc.bDeviceClass));
    ui->plainTextEdit->insertPlainText("  ");
    ui->plainTextEdit->insertPlainText("VendorID: ");
    ui->plainTextEdit->insertPlainText(QString::number(desc.idVendor));
    ui->plainTextEdit->insertPlainText("  ");
    ui->plainTextEdit->insertPlainText("ProductID: ");
    ui->plainTextEdit->insertPlainText(QString::number(desc.idProduct));
    ui->plainTextEdit->insertPlainText("\n");
    libusb_config_descriptor *config;
    libusb_get_config_descriptor(dev, 0, &config);
    ui->plainTextEdit->insertPlainText("Interfaces: ");
    ui->plainTextEdit->insertPlainText(QString::number((int)config->bNumInterfaces));
    ui->plainTextEdit->insertPlainText(" ||| ");
    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    const libusb_endpoint_descriptor *epdesc;
    for(int i=0; i<(int)config->bNumInterfaces; i++) {
        inter = &config->interface[i];
        ui->plainTextEdit->insertPlainText("Number of alternate settings: ");
        ui->plainTextEdit->insertPlainText(QString::number(inter->num_altsetting));
        ui->plainTextEdit->insertPlainText(" | ");
        for(int j=0; j<inter->num_altsetting; j++) {
            interdesc = &inter->altsetting[j];
            ui->plainTextEdit->insertPlainText("Interface Number ");
            ui->plainTextEdit->insertPlainText(QString::number((int)interdesc->bInterfaceNumber));
            ui->plainTextEdit->insertPlainText(" | ");
            ui->plainTextEdit->insertPlainText("Number of endpoints: ");
            ui->plainTextEdit->insertPlainText(QString::number((int)interdesc->bNumEndpoints));
            ui->plainTextEdit->insertPlainText(" | ");
            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
                epdesc = &interdesc->endpoint[k];
                ui->plainTextEdit->insertPlainText("Descriptor Type; ");
                ui->plainTextEdit->insertPlainText(QString::number((int)epdesc->bDescriptorType));
                ui->plainTextEdit->insertPlainText(" | ");
                ui->plainTextEdit->insertPlainText("EP Address: ");
                ui->plainTextEdit->insertPlainText(QString::number((int)epdesc->bEndpointAddress));
                ui->plainTextEdit->insertPlainText(" | ");
            }
        }
    }
    ui->plainTextEdit->insertPlainText("\n\n\n");
    libusb_free_config_descriptor(config);
}
