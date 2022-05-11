#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <boost/asio.hpp>

const double shuntResistance = 0.107;

int main() {
    boost::asio::io_service io;
    boost::asio::serial_port serial(io);

    serial.open("/dev/tty.usbmodem14101");
    serial.set_option(boost::asio::serial_port_base::baud_rate(115200));
    
    char buf[7];
    
    while(1) {
        memmove(buf, &buf[1], 6);
        boost::asio::read(serial, boost::asio::buffer(&buf[6], 1));
        if (std::string(buf,7) == "#!#!#!\n") break;
    }

    double time = 0.0;
    std::ofstream fout("log.csv");
    std::chrono::time_point<std::chrono::steady_clock> start;    
    start = std::chrono::steady_clock::now();

    while(std::chrono::steady_clock::now() - start < std::chrono::minutes(10)) {
        uint8_t data[80]; // is this OK or should it be pre-loop
        int nread = boost::asio::read(serial, boost::asio::buffer(data, 80));
    
        for (int i=0; i<80; i+=4) {
            double shuntVoltage = *((int16_t*)&data[i]) * 2.5e-6;
            double busVoltage = *((uint16_t*)&data[i+2]) * 1.25e-3;

            double current = shuntVoltage / shuntResistance;    

            double power = current*busVoltage;

            fout<<time<<","<<shuntVoltage<<","<<busVoltage<<","<<current<<","<<power<<"\n";
            // std::cout<<time<<","<<shuntVoltage<<","<<busVoltage<<","<<current<<","<<power<<"\n";
            // time+=0.001176;
            time+=0.000664;
        }
    }

    fout.close();
}